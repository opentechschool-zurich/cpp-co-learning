#include "ViewOne.h"
#include <iostream>

using namespace std;

ViewOne::ViewOne() : updateCounts{0} {}

void ViewOne::operator ()(int value)
{
    cout << "View ONE updated " << ++updateCounts << " times (new value: " << value << ")" << endl;
}

//void ViewOne::update()
//{
//    cout << "View ONE updated " << ++updateCounts << " times" << endl;
//}
