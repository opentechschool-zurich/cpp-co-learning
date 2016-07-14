#pragma once

class PriceObserver {
public:
    virtual void newPriceCallback(float price);
};