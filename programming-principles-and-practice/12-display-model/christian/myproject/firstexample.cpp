#include "../../guicode/Simple_window.h" // window library 
#include "../../guicode/Graph.h"

int main()
{
  using namespace Graph_lib;

  Point tl {100, 100};

  Simple_window win {tl, 600, 400, "My window"};

  win.wait_for_button();// give control to the display engine and thus
                        // display the window on screen 
}

 
