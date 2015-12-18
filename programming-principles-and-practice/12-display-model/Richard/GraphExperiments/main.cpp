#include "Simple_window.h"
//#include "Graph.h"  
#include "Point.h"

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char **argv) {
    using namespace Graph_lib;

    Point topLeftWindowCorner{100, 100};

    Simple_window win{topLeftWindowCorner, 600, 400, "Canvas"};

    Graph_lib::Polygon poly;
    poly.add(Point{300, 200}); // add a point
    poly.add(Point{350, 100}); // add another point
    poly.add(Point{400, 200}); // add a third point
    poly.set_color(Color::red); // adjust properties of poly
    win.attach(poly); // connect poly to the window

    Graph_lib::Polygon poly2;
    poly2.add(Point{100, 150}); // add a point
    poly2.add(Point{250, 350}); // add another point
    poly2.add(Point{80, 280}); // add a third point
    poly2.add(Point{20, 200}); // add a third point
    poly2.set_color(Color::dark_cyan); // adjust properties of poly
    //poly2.fill_color(Color::dark_cyan);
    win.attach(poly2); // connect poly to the window

    Axis xa{Axis::x, Point
        {20, 300}, 280, 10, "x axis"};
    win.attach(xa); // attach xa to the window, win
    win.set_label("Canvas #2");

    Axis ya{Axis::y, Point
        {20, 300}, 280, 10, "y axis"};
    ya.set_color(Color::cyan); // choose a color
    ya.label.set_color(Color::dark_red); // choose a color for the text
    win.attach(ya);
    win.set_label("Canvas #3");


    Function sine {sin,0,100,Point{20,150},1000,50,50};
    win.attach(sine);
    
    Fl_Window *window = new Fl_Window(340, 180);
    Fl_Box *box = new Fl_Box(20, 40, 300, 100, "Hello, World!");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD + FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);
    //win.attach(box);
    window->end();
    window->show(argc, argv);
    Fl::run();

    win.wait_for_button(); // give control to the display engine
    return 0;
}
