#ifndef OOP_LAB7_SQUARE_H
#define OOP_LAB7_SQUARE_H

#include "figure.h"

namespace figures {

    class Square : public Figure {
    private:
        Dot *coordinates;
    public:
        Square();
        explicit Square(std::istream& is);
        Dot Center() const override;
        double Area() const override ;
        void PrintOut(std::ostream& os) const override;
        friend std::ostream& operator<<(std::ostream& os, const Square& A);
        ~Square() override;
    };

} //namespace figures

class Square_factory : public FactoryInterface {
public:
    std::shared_ptr<figures::Figure> Figure_create() const override;
    std::shared_ptr<figures::Figure> Figure_create(std::istream& is) const override;
};

#endif //OOP_LAB7_SQUARE_H
