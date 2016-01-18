#ifndef SMILEY_H
#define SMILEY_H

#include "Graph.h"

class Smiley {
public:

    Smiley(Simple_window & win, int x, int y) {
        Circle *rimPointer = new Circle{Point
            { x, y}, 100};
        win.attach(*rimPointer);

        Circle *leftEyePointer = new Circle{Point
            { x - 30, y - 30}, 10};
        win.attach(*leftEyePointer);

        Circle *rightEyePointer = new Circle{Point
            { x + 30, y - 30}, 10};
        win.attach(*rightEyePointer);

        Graph_lib::Ellipse *nosePointer = new Graph_lib::Ellipse{Point
            { x, y}, 5, 20};
        win.attach(*nosePointer);

		Graph_lib::Arc *mouthArc = new Graph_lib::Arc{Point
            {x, y + 8}, 55, 210.0, 330.0};
        win.attach(*mouthArc);
    }
};

#endif /* SMILEY_H */

