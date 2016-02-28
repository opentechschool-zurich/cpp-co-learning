#include "Smiley.h"

#include <iostream>

Smiley::Smiley(Simple_window& win, int x, int y)
: rim(Point{x, y}, 100),
leftEye(Point{x - 30, y - 30}, 10),
rightEye(Point{x + 30, y - 30}, 10),
nose(Point{x, y}, 5, 20),
mouth(Point{x, y + 8}, 55, 210.0, 330.0)
{
    std::cout << "Constructor running on a smiley" << std::endl;
    win.attach(rim);
    win.attach(leftEye);
    win.attach(rightEye);
    win.attach(nose);
    win.attach(mouth);
}

Smiley::~Smiley() {
    std::cout << "Destructor running on a smiley" << std::endl;
}
