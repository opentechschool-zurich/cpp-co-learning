#include "Menues_window.h"
#include "window-graph/Window.h"
#include "window-graph/GUI.h"  

using namespace Graph_lib;

Menues_window::Menues_window(Point xy, int w, int h, const string& title)
    :Window(xy, w, h, title),
    menu_button(Point(x_max()-80,30), 80, 20, "color menu", [](Address, Address w){reference_to<Menues_window>(w).menu_pressed();}),
    color_menu{Point{x_max()-70, 40}, 70, 20, Menu::vertical, "color"},
	circle{ Point{ 100,100 }, 100 }
{
	attach(circle);

	attach(menu_button);

    color_menu.attach(new Button{Point{0,0}, 0, 0, "red", [](Address, Address w) {reference_to<Menues_window>(w).red_pressed();}});
    color_menu.attach(new Button{Point{0,0}, 0, 0, "blue", [](Address, Address w) {reference_to<Menues_window>(w).blue_pressed();}});
    color_menu.attach(new Button{Point{0,0}, 0, 0, "black", [](Address, Address w) {reference_to<Menues_window>(w).black_pressed();}});
    attach(color_menu);
    color_menu.hide();
}
