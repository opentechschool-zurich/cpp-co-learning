#include "PricePublisher.h"
#include <iostream>

PricePublisher::PricePublisher() {
    std::cout << "Constructing PricePublisher\n";
}

void PricePublisher::publishNextPrice() {
    float price = aapl[stockindex++ % aapl.size()]; // notice the double cleverness of postincrement and modulo size!
    std::cout << "Publishing price[" << stockindex - 1 << "] = " << price << "\n";
    for ( auto priceObserver : priceObservers ) {
        priceObserver->newPriceCallback(price);
    }
}

void PricePublisher::registerPriceObserver(PriceObserver* priceObserver) {
    std::cout << "Registering an observer" << std::endl;
    priceObservers.push_back(priceObserver);
}