#include "Simple_window.h"
#include "Point.h"
#include "Smiley.h"

using namespace Graph_lib;

void smiley(Simple_window &, int, int);

int main() {
    Point topLeftWindowCorner{100, 100};
    Simple_window simple_win{topLeftWindowCorner, 600, 420, "AcidCanvas"};

    Smiley s1 {simple_win, 100, 100};
    Smiley s2 {simple_win, 300, 100};
    Smiley s3 {simple_win, 100, 300};
    Smiley s4 {simple_win, 300, 300};

    simple_win.wait_for_button();
    return 0;
}



