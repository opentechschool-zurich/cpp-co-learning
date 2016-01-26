#include <iostream>
#include "Rectangle.h"

using namespace std;

int main()
{
    Rectangle rectangle{};
    rectangle.setWidth(10);
    rectangle.setHeight(5);
    cout << "Area: " << rectangle.getArea() << endl;
    return 0;
}
