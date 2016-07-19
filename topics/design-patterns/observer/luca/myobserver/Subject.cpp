#include "Subject.h"

Subject::Subject(int initialState) :
    myStateX {initialState}
{}

void Subject::setStateX(int newValue)
{
    myStateX = newValue;
    notifyStateX();
}

void Subject::notifyStateX()
{
    // take all the observers for EventX
    std::pair<ObserverIterator, ObserverIterator> rangei = registeredThings.equal_range(EventX);

    // loop all the observer registered to
    for ( ObserverIterator i = rangei.first;
          i != registeredThings.end() && i != rangei.second; // not past-the-end and not finished
          ++i
        )
    {
        // and call them
        (*i).second(myStateX);
    }
}
