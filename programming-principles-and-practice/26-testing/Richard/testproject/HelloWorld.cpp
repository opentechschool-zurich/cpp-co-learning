#include <iostream>
#include "sumnumbers.h"
#include "multnumbers.h"

using namespace std;

int main(int argc, char **argv) {
	cout << "Hello World" << endl;
	cout << "sumnumbers(12, 13) returned: " << sumnumbers(12, 13) << endl;
	cout << "sumnumbers(10, 12) returned: " << sumnumbers(10, 12) << endl;
	cout << "multnumbers(2, 4) returned: " << multnumbers(2, 4) << endl;
	cout << "multnumbers(10, 12) returned: " << multnumbers(10, 12) << endl;
}
