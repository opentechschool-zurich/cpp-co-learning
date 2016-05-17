#include <iostream>
#include "sumnumbers.h"
#include "multnumbers.h"
#include "triangle_type.h"

using namespace std;

/*! \mainpage An Example of using Google Test with triangles
 *
 * \image html Diagram.png
 */

int main(int argc, char **argv) {
	cout << "Hello World" << endl;
	cout << "sumnumbers(12, 13) returned: " << sumnumbers(12, 13) << endl;
	cout << "sumnumbers(10, 12) returned: " << sumnumbers(10, 12) << endl;
	cout << "multnumbers(2, 4) returned: " << multnumbers(2, 4) << endl;
	cout << "multnumbers(10, 12) returned: " << multnumbers(10, 12) << endl;
	cout << "triangle_type (4, 4, 4) returns: " << triangle_type(4, 4, 4) << endl;
	cout << "triangle_type (4, 4, 2) returns: " << triangle_type(4, 4, 2) << endl;
}
