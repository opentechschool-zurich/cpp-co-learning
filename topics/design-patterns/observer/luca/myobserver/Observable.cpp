#include "Observable.h"

Observable::Observable()
    : registeredThings{}
{}

//bool Observable::registerObserver(EventType type, ObserverInt &slave)
bool Observable::registerObserver(EventType type, multimapValue slave)
{
    registeredThings.insert(std::pair<EventType, multimapValue>(type, slave));
    return true;
}

bool Observable::deregisterObservers(EventType t)
{
    // not sure about this
    //registeredThings.erase(registeredThings.equal_range(t));

    return false;
}

