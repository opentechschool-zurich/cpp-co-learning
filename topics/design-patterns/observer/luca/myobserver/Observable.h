#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <map>
#include <functional>

using namespace std;

enum EventType {
    Event1,
    EventX
};
typedef function<void(int)> multimapValue;

class Observable
{
protected:
    multimap<EventType, multimapValue> registeredThings;

public:
    typedef multimap<EventType, multimapValue>::iterator ObserverIterator;

    Observable();
    /**
     * setup a new observer to this register
     * @param slave
     * @return successful or not
     */
    bool registerObserver(EventType type, multimapValue slave);

    /**
     * @brief deregisterObserver @todo How to identify the one to drop?
     * @param slave
     * @return successful or not
     */
    bool deregisterObservers(EventType t);

//    /**
//     * @brief notifyStateX it does the observer loop
//     */
//    void notifyStateX();
};

#endif // OBSERVABLE_H
