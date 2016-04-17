#include "Simple_window.h"
#include "Point.h"
#include "Arc.h"

using namespace Graph_lib;

void smiley(Simple_window &, int, int);

int main() {
	Point topLeftWindowCorner{ 100,100 };
    int windowWidth = 600, windosHeight = 420;   
	Simple_window simple_win{ topLeftWindowCorner, windowWidth, windosHeight, ":: smile ::" };
	
    // call window with smiley
    // objects attached by pointer to survive call
    int faceFromLeft = 250, faceFromTop = 100;
	smiley(simple_win, faceFromLeft, faceFromTop);  

	simple_win.wait_for_button();
	return 0;
}

/*
 * Graphic classes are given by reference (trought construct them by 
 * the keyword new). 
 */
void smiley(Simple_window & win, int x, int y) {

    // Gesichtsgrösse:   Rectangel-Gesicht p.885 (epub reader)
    int width = 200, hight = 300;
    Rectangle *face = new Rectangle { Point{x,y}, width, hight};
    win.attach(*face);  // Wert des Pointers übergeben
    face->set_fill_color(180);  // White = 255, Black = 0, Blue =136, Yellow = 76
    /*// Circle: Point nennt das Zentrum des Gesichts
    int radius = 150;
	Circle *rimPointer = new Circle { Point{ x,y }, radius};
	win.attach( *rimPointer);  */

    // Augen
    // top left face( -> 250, | 100)
    int radiusEyeLeft = 25;
	Circle *leftEyePointer = new  Circle {Point{ x+radiusEyeLeft+18, y+radiusEyeLeft+43 }, radiusEyeLeft};
	win.attach( *leftEyePointer);
    leftEyePointer->set_fill_color(129); 
    int radiusEyeRight = 25;
	Circle *rightEyePointer = new Circle { Point{ x+radiusEyeRight+113,y+radiusEyeRight+69 },radiusEyeRight }; 
	win.attach( *rightEyePointer );
    rightEyePointer->set_fill_color(30);

    // Nase
    // top left face( -> 250, | 100), Breite = 200, Höhe = 300
    int noseWidth = 5, noseHight = 20;
	Graph_lib::Ellipse *nosePointer = new Graph_lib::Ellipse { Point{x+100, y+150 }, noseWidth,noseHight};
	win.attach(*nosePointer);
    nosePointer->set_fill_color(035);
	
    // Mund
    // top left face( -> 250, | 100)
	Graph_lib::Polygon *mouthPointer = new Graph_lib::Polygon;
	(*mouthPointer).add(Point{ x+50,y + 200 });
	(*mouthPointer).add(Point{ x+75,y + 205 });
	(*mouthPointer).add(Point{ x+100,y + 208 });
	(*mouthPointer).add(Point{ x + 125,y + 205 });
	(*mouthPointer).add(Point{ x + 150,y + 200 });
	win.attach(*mouthPointer);
    mouthPointer->set_fill_color(Color::dark_red);

	return;
}
