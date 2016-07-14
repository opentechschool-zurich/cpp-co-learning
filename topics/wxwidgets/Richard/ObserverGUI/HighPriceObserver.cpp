#include "HighPriceObserver.h"
#include <iostream>

HighPriceObserver::HighPriceObserver(wxTextCtrl* myTextCtrl) : textCtrl(myTextCtrl) {
}

void HighPriceObserver::newPriceCallback(float price) {
    if (price > highWatermark) {
        highWatermark = price;
        textCtrl->Clear();
        *textCtrl << price;
    }
}

