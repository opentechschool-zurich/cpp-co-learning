// chapter 12
//
// be shure about format

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <string>
#include "std_lib_facilities.h"

#include "Simple_window.h"
#include "Graph.h"

using namespace std;
 

 
int main()
{
	using namespace Graph_lib;
	
	Point tl{100, 100}; // top left
	Simple_window win {tl, 600, 400, "Canvas"};

	Polygon poly;
	poly.add(Point{300,200});
	poly.add(Point{350, 100});
	
	poly.set_color(Color::red);
	
	win.attach(poly);
	
	win.wait_for_button();
	
	cout << "\n";
	
}
