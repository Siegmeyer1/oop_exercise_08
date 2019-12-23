#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "figures/triangle.h"
#include "figures/square.h"
#include "figures/octagon.h"
#include "subscribers.h"

class Factory {
public:
    std::map<std::string, std::shared_ptr<FactoryInterface>> plants;
    Factory() {
        plants.emplace("triangle", std::make_shared<Triangle_factory>());
        plants.emplace("square", std::make_shared<Square_factory>());
        plants.emplace("octagon", std::make_shared<Octagon_factory>());
    }
};

int main(int args, char* argv[]) {
    if (args < 2) {
        std::cout << "USAGE: ./oop_exercise_08 [size of buffer]\n";
        return -1;
    }
    long buf_size = strtol(argv[1], nullptr, 10);
    std::vector<std::shared_ptr<figures::Figure>> buffer;
    buffer.reserve(buf_size);
    Factory factory;
    std::string command;

    std::condition_variable cv;
    std::condition_variable cv2;
    std::mutex mutex;
    bool done = false;
    int a = 1;

    std::vector<std::shared_ptr<SubscriberInterface>> subscribers;
    subscribers.push_back(std::make_shared<ConsolePrint>());
    subscribers.push_back(std::make_shared<DocumentPrint>());

    std::thread subscriber([&]() {
        std::unique_lock<std::mutex> subscriber_lock(mutex);
        while(!done) {
            cv.wait(subscriber_lock);
            if (done) {
                cv2.notify_all();
                break;
            }
            for (int i = 0; i < 2; ++i) {
                subscribers[i]->output(buffer);
            }
            buffer.resize(0);
            ++a;
            cv2.notify_all();
        }
    });

    while(command != "quit") {
        std::cin >> command;
        if (command == "quit") {
            done = true;
            cv.notify_all();
            break;
        } else if (command == "triangle" || command == "square" || command == "octagon") {
            auto tmp = factory.plants[command]->Figure_create(std::cin);
            std::unique_lock<std::mutex> main_lock(mutex);
            buffer.push_back(tmp);
            if (buffer.size() == buffer.capacity()) {
                cv.notify_all();
                cv2.wait(main_lock);
            }
        } else {
            std::cout << "no such figure\n";
        }
    }
    subscriber.join();
    return 0;
}