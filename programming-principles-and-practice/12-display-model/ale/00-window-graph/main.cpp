#include "Simple_window.h"
#include "Graph.h"
int main() {
    using namespace Graph_lib;

    Point tl {100,100};

    Simple_window win {tl,600,400,"Canvas"};

    Polygon poly;

    poly.add(Point{300,200}); // add a point
    poly.add(Point{350,100}); // add another point
    poly.add(Point{400,200}); // add a third point

    poly.set_color(Color::red); // adjust properties of poly

    win.attach (poly); // connect poly to the window

    win.wait_for_button(); // give control to the display engine
    return 0;
}
