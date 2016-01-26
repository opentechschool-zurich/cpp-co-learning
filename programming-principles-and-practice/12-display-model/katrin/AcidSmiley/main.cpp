#include "Simple_window.h"
#include "Point.h"

using namespace Graph_lib;

void smiley(Simple_window &, int, int);

int main() {
	Point topLeftWindowCorner{ 100,100 };
	Simple_window simple_win{ topLeftWindowCorner, 600, 420, "AcidCanvas" };
	
	smiley(simple_win, 300, 200); // x, y 

	simple_win.wait_for_button();
	return 0;
}

/*
There are a couple of Gotchas with this code!
If we have all the Circle and Ellipse variables in main() we can write
the code like this:

Graph_lib::Ellipse nose{ Point{ x,y }, 5,20 };
win.attach(nose);

But if we take this code to a function we have to consider
the following:

First we have to pass the Simple_window variable by reference 
so that we attach our shapes to the correct window.

Next if we write the code as above the variable "nose" is destroyed
when our function ends; it is only a local variable! Since the FLTK
system only looks for our shapes when we call wait_for_button they are
gone and FLTK draws nothing.

To create the shape objects and keep them around longer than the 
function exists we need to use the "new" keyword. With new we can ask
for an object to be created and we get back a pointer to it's
memory location. We can then attach the object in that memory 
location to the window with the * operator. I.e.

Graph_lib::Ellipse *nosePointer = new Graph_lib::Ellipse { Point{ x,y }, 5,20 };
win.attach( *nosePointer );

*/
void smiley(Simple_window & win, int x, int y) {

    // Gesichtsgrösse
	Circle *rimPointer = new Circle { Point{ x,y }, 150 }; // Radius
	win.attach( *rimPointer);
    rimPointer->set_color(Color::dark_red);
    
    //Rectangel-Gesicht;

    // Augen
	Circle *leftEyePointer = new  Circle { Point{ x - 70,y - 9 }, 35 };
	win.attach( *leftEyePointer);
    leftEyePointer->set_fill_color(Color::black);

	Circle *rightEyePointer = new Circle { Point{ x + 50,y -50 }, 25 }; 
	win.attach( *rightEyePointer );
    rightEyePointer->set_color(Color::black);

    // Nase
	Graph_lib::Ellipse *nosePointer = new Graph_lib::Ellipse { Point{ x,y }, 5,20 };
	win.attach( *nosePointer );
	
    // Mund
    // - Klasse Arc selber implementieren
    // - Polyline Mund ersetzen durch Arc
    // - AcidSmile nicht als Funktion, sondern als Klasse
	Graph_lib::Polygon *mouthPointer = new Graph_lib::Polygon;
	(*mouthPointer).add(Point{ x - 50,y + 60 });
	(*mouthPointer).add(Point{ x - 25,y + 65 });
	(*mouthPointer).add(Point{ x,y + 68 });
	(*mouthPointer).add(Point{ x + 25,y + 65 });
	(*mouthPointer).add(Point{ x + 50,y + 60 });
	win.attach(*mouthPointer);

	return;
}
