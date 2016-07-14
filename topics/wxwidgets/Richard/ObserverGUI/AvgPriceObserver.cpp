#include "AvgPriceObserver.h"
#include <iostream>

AvgPriceObserver::AvgPriceObserver(wxTextCtrl* myTextCtrl) : textCtrl(myTextCtrl) {
}

void AvgPriceObserver::newPriceCallback(float price) {
    sum += price;
    ++counter;
    textCtrl->Clear();
    *textCtrl << sum / counter;
}

