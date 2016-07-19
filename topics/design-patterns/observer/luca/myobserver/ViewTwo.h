#ifndef VIEWTWO_H
#define VIEWTWO_H

#include "Observer.h"
#include <string>

using namespace std;

class ViewTwo : public ObserverInt
{
private:
    string myname;
public:
    explicit ViewTwo(const string &name);
    ~ViewTwo() {}

    // ObserverInt interface
    virtual void operator ()(int value);
};

#endif // VIEWTWO_H
