#include <iostream>
#include "Square.h"

using namespace std;

int main()
{
    Square square{};
    square.setWidth(10);
    square.setHeight(5);
    cout << "Area: " << square.getArea() << endl;
    return 0;
}
