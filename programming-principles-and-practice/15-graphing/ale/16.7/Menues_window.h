#include <iostream>
#include "window-graph/Window.h"
#include "window-graph/Graph.h"  
#include "window-graph/GUI.h"  
#include "window-graph/Point.h"

namespace Graph_lib {

class Menues_window : Window
{
public:
	Menues_window(Point xy, int w, int h, const string& title);

    Menu color_menu;
    Circle circle;

	// the actions:
	void red_pressed() { change(Color::red); }
	void blue_pressed() { change(Color::blue); }
	void black_pressed() { change(Color::black); }
	void change(Color c) { std::cout << "new color" << std::endl; circle.set_color(c); }
};

}
