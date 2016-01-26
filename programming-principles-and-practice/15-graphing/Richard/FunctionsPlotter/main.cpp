#include "Simple_window.h" 
#include "Point.h"

constexpr int xmax = 600; // window size 
constexpr int ymax = 400;

constexpr int x_orig = xmax / 2; // position of (0,0) is center of window
constexpr int y_orig = ymax / 2;

constexpr int r_min = -10; // range -10 .. 11 
constexpr int r_max = 11;

constexpr int n_points = 400; // number of points used in range

constexpr int x_scale = 30; // scaling factors 
constexpr int y_scale = 30;

constexpr int xlength = xmax - 40; // make the axis a bit smaller than the window
constexpr int ylength = ymax - 40;

double one(double) {
    return 1;
}

double slope(double x) {
    return x / 2;
}

double square(double x) {
    return x*x;
}

double sloping_cos(double x) {
    return cos(x) + slope(x);
}

int main() {
    Point orig{x_orig, y_orig};
    Simple_window win{Point
        {100, 100}, xmax, ymax, "Function graphing"};

    Function s{one, r_min, r_max, orig, n_points, x_scale, y_scale};
    win.attach(s);
    Function s2{slope, r_min, r_max, orig, n_points, x_scale, y_scale};
    win.attach(s2);
    Function s3{square, r_min, r_max, orig, n_points, x_scale, y_scale};
    win.attach(s3);
    Function s4{sqrt, r_min, r_max, orig};
    win.attach(s4);
    Function s5{cos, r_min, r_max, orig, 400, 30, 30};
    s5.set_color(Color::blue);
    win.attach(s5);
    Function s6{sloping_cos, r_min, r_max, orig, 400, 30, 30};
    win.attach(s6);

    Function f1{log, 0.000001, r_max, orig, 200, 30, 30}; // log() logarithm, base e
    win.attach(f1);
    Function f2{sin, r_min, r_max, orig, 200, 30, 30}; // sin()
    win.attach(f2);
    f2.set_color(Color::blue);
    Function f3{cos, r_min, r_max, orig, 200, 30, 30}; // cos()
    win.attach(f3);
    Function f4{exp, r_min, 5, orig, 200, 30, 30}; // exp() exponential e^x    
    win.attach(f4);

    // Lambdra Expreession [] means lambda introducer (double x) means input values {return ...} is what the Lambda returns
    Function s7{[](double x) {
            return cos(x) + slope(x);
        }, r_min, r_max, orig, 400, 30, 30};
    win.attach(s7);

    // Lambda with different syntax
    Function s8{[](double x) -> double {
            return cos(x) + slope(x) + 1;
        }, r_min, r_max, orig, 400, 30, 30};
    win.attach(s8);

    Text ts{Point
        {100, y_orig - 40}, "one"};
    win.attach(ts);
    Text ts2{Point
        {100, y_orig + y_orig / 2 - 20}, "x/2"};
    win.attach(ts2);
    Text ts3{Point
        {x_orig - 100, 20}, "x*x"};
    win.attach(ts3);
    Text ts4{Point
        {460, y_orig - 50}, "sqrt"};
    win.attach(ts4);
    win.set_label("Function graphing: label functions");

    Axis x{Axis::x, Point
        {20, y_orig},
        xlength, xlength / x_scale, "one notch == 1"};
    x.set_color(Color::red);
    win.attach(x);
    Axis y{Axis::y, Point
        {x_orig, ylength + 20},
        ylength, ylength / y_scale, "one notch == 1"};
    y.set_color(Color::red);
    win.attach(y);

    x.label.move(160, 0);
    x.notches.set_color(Color::dark_red);

    win.wait_for_button();
    return 0;
}
