#include "Menues_window.h"
#include "window-graph/Window.h"
#include "window-graph/GUI.h"  

using namespace Graph_lib;

Menues_window::Menues_window(Point xy, int w, int h, const string& title)
    :Window(xy, w, h, title),
    color_menu{Point{x_max()-70, 40}, 70, 20, Menu::vertical, "color"},
	circle{ Point{ 100,100 }, 100 }
{
	attach(circle);
    color_menu.attach(new Button{Point{0,0}, 0, 0, "red", [](Address, Address w) {reference_to<Menues_window>(w).red_pressed();}});
    attach(color_menu);
}
