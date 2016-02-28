#pragma once

#include "Simple_window.h"
#include "Graph.h"

class Smiley {
public:
    Smiley(Simple_window& win, int x, int y);
    ~Smiley();
private:
    Circle rim;
    Circle leftEye;
    Circle rightEye;
    Ellipse nose;
    Arc mouth;
};


