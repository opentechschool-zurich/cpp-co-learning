#include <iostream>
#include "Rectangle.h"
#include "Square.h"

using namespace std;

int main()
{
    Rectangle rectangle{};
    rectangle.setWidth(10);
    rectangle.setHeight(5);
    cout << "Area: " << rectangle.getArea() << endl;
    Square square = static_cast<Square>(rectangle);
    cout << "Square Area: " << square.getArea() << endl;
    return 0;
}
