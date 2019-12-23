//
// Created by anri on 22.12.2019.
//

#ifndef OOP_LAB8_SUBSCRIBERS_H
#define OOP_LAB8_SUBSCRIBERS_H

class SubscriberInterface {
public:
    virtual void output(std::vector<std::shared_ptr<figures::Figure>>) = 0;
    virtual ~SubscriberInterface() = default;
};

class ConsolePrint : public SubscriberInterface {
public:
    void output(std::vector<std::shared_ptr<figures::Figure>> buffer) override {
        for (auto& figure : buffer) {
            figure->PrintOut(std::cout);
        }
    }
};

class DocumentPrint : public SubscriberInterface {
public:
    DocumentPrint() : a(1) {}
    void output(std::vector<std::shared_ptr<figures::Figure>> buffer) override {
        std::string name = std::to_string(a);
        name += ".txt";
        std::ofstream file;
        file.open(name);
        if(!file.is_open())
        {
            file.clear();
            file.open(name, std::ios::out);
            file.close();
            file.open(name);
        }
        for (auto &figure : buffer) {
            figure->PrintOut(file);
        }
        ++a;
    }
private:
    int a;
};

#endif //OOP_LAB8_SUBSCRIBERS_H
