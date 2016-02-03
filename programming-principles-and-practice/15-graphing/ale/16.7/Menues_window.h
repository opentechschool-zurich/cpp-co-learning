#include "window-graph/Window.h"
#include "window-graph/Graph.h"  
#include "window-graph/GUI.h"  
#include "window-graph/Point.h"

namespace Graph_lib {

class Menues_window : Window
{
public:
	Menues_window(Point xy, int w, int h, const string& title);

    Button menu_button;
    Menu color_menu;
    Circle circle;

	// the actions:
	void menu_pressed() { menu_button.hide(); color_menu.show(); }
	void menu_hide() { menu_button.show(); color_menu.hide(); }
	void red_pressed() { change(Color::red); menu_hide(); }
	void blue_pressed() { change(Color::blue); menu_hide(); }
	void black_pressed() { change(Color::black); menu_hide(); }
	void change(Color c) {circle.set_color(c); redraw();}
};

}
