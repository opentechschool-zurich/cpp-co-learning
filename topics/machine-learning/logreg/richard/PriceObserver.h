#pragma once

/**
* An abstract class for other classes to inherit from who want to receive a price
*/
class PriceObserver {
public:
    /**
    * the overriding class will be notified on this pure virtual
    * method of the new price
    */
    virtual void newPriceCallback(float price) = 0;
};
