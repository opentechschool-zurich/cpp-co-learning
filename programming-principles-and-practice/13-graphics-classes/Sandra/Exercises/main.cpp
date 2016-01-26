#include "Simple_window.h"
#include "Point.h"

using namespace Graph_lib;

int main() {
	Point topLeftWindowCorner{ 100,100 };
	Simple_window simple_win{ topLeftWindowCorner, 800, 1000, "Exercise Canvas" };

	Lines gridLinesObject;
	for (int x = 100; x < 800; x += 100)
		gridLinesObject.add(Point{ x, 0 }, Point{ x, 800 });
	for (int y = 100; y <= 800; y += 100)
		gridLinesObject.add(Point{ 0, y }, Point{ 800, y });
	simple_win.attach(gridLinesObject);

// red rectangles down the screen
	for (int x = 0; x <= 800; x += 100) {
		Graph_lib::Rectangle *rect = new Graph_lib::Rectangle { Point{ x, x }, 100, 100 };
		(*rect).set_fill_color(Color::red);
		simple_win.attach(*rect);
	}

	simple_win.wait_for_button();
	return 0;
}
