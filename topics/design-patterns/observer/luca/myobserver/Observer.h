#ifndef OBSERVER_H
#define OBSERVER_H

class ObserverInt
{
public:
    ObserverInt();
//    virtual void update() = 0;

    virtual ~ObserverInt() {}

    virtual void operator()(int value) = 0;
};

#endif // OBSERVER_H
