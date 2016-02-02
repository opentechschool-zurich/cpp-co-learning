#include "Square.h"

class Rectangle : public Square
{
public:
    void setHeight(const int h) {height = h;};
    int getArea() const;
    int getGlitch() const override {return 3;} 
private:
    int height{0};
};
