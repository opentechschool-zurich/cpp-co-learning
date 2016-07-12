#ifndef VIEWONE_H
#define VIEWONE_H

#include "Observer.h"

class ViewOne : public ObserverInt
{
private:
    int updateCounts;

public:
    ViewOne();
    ~ViewOne() {}

    //virtual void update();
    virtual void operator ()(int value);
};

#endif // VIEWONE_H
