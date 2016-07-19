#include <iostream>

#include "Subject.h"
#include "ViewOne.h"
#include "ViewTwo.h"

using namespace std;



int main()
{
    Subject publisher;
    ViewOne v1;
    ViewTwo v2 {"first"};
    ViewTwo v3 {"second"};

    publisher.registerObserver(EventX, v1);
    publisher.registerObserver(EventX, v2);
    publisher.registerObserver(Event1, v3); // this will be not notified

    publisher.setStateX(10);
    publisher.setStateX(1000);
    publisher.setStateX(5);

    return 0;
}

