#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Simple_window : Graph_lib::Window {
	Simple_window(Point xy, int w, int h, const string& title );
	
	bool wait_for_button();

	Button next_button;
private:
	bool button_pushed;
	
	static void cb_next(Address, Address addr); // callback for next_button
	//	{ reference_to<Simple_window>(addr).next(); }

	void next();

};
