#include "PriceObserver.h"
#include <iostream>

void PriceObserver::newPriceCallback(float price) {
    std::cout << "Price Observerd: " << price << std::endl;
}

