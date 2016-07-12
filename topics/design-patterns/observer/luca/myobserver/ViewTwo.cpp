#include "ViewTwo.h"
#include <iostream>

using namespace std;

ViewTwo::ViewTwo(const string &name)
    : myname{name}
{}

void ViewTwo::operator ()(int value)
{
    cout << "view2 " << myname << " notified.." << endl;
}
