#include "Square.h"

class Rectangle : Square
{
public:
    void setHeight(const int h) {height = h;};
private:
    int height{0};
};
