#include "LowPriceObserver.h"
#include <iostream>

LowPriceObserver::LowPriceObserver(wxTextCtrl* myTextCtrl) : textCtrl(myTextCtrl) {
}

void LowPriceObserver::newPriceCallback(float price) {
    if (price < lowWatermark) {
        lowWatermark = price;
        textCtrl->Clear();
        *textCtrl << price;
    }
}

