#include "window-graph/Point.h"
#include "Menues_window.h"

int main() {

    using namespace Graph_lib;

    Point tl {100,100};

    try {
        Menues_window win {tl,600,400,"With windows"};
        return gui_main();
    } catch  (exception& e) {
    }

    return 0;
}
