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
    poly.set_style(Line_style(Line_style::dash, 4));
    win.attach(poly); // connect poly to the window

    Graph_lib::Polygon poly2;
    poly2.add(Point{100, 150}); // add a point
    poly2.add(Point{250, 350}); // add another point
    poly2.add(Point{80, 280}); // add a third point
    poly2.add(Point{20, 200}); // add a third point
    poly2.set_color(Color::dark_cyan); // adjust properties of poly
    poly2.set_style(Line_style::dash);
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


    Function sine{sin, 0, 100, Point
        {20, 150}, 1000, 50, 50};
    win.attach(sine);

    Rectangle r{Point
        {200, 200}, 100, 50};
    r.set_fill_color(Color::yellow);
    win.attach(r);

    Closed_polyline poly_rect;
    poly_rect.add(Point{100, 50});
    poly_rect.add(Point{200, 50});
    poly_rect.add(Point{200, 100});
    poly_rect.add(Point{100, 100});
    poly_rect.add(Point{50, 75});
    poly_rect.set_style(Line_style(Line_style::dash, 2));
    poly_rect.set_fill_color(Color::green);
    win.attach(poly_rect);

    Text t{Point
        {150, 150}, "Hello, graphical world!"};
    //t.set_font(Font::times_bold);
    t.set_font_size(20);
    win.attach(t);
    
    Image ii {Point{330,250},"image.jpg"};
    win.attach(ii);

    Circle c {Point{100,200},50};
    win.attach(c);
    
    Ellipse e {Point{100,200}, 75,25};
    e.set_color(Color::dark_red);
    win.attach(e);
    
    Mark m {Point{100,200},'x'};
    win.attach(m);

    ostringstream oss;
    oss << "screen size: " << x_max() << "*" << y_max()
    << "; window size: " << win.x_max() << "*" << win.y_max();
    Text sizes {Point{100,20},oss.str()};
    win.attach(sizes);
    
    
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
