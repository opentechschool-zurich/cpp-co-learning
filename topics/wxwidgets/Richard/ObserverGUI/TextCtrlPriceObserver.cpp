#include "TextCtrlPriceObserver.h"
#include <iostream>

TextCtrlPriceObserver::TextCtrlPriceObserver( wxTextCtrl* myTextCtrl) : textCtrl(myTextCtrl) {
    //std::cout << "Constructing a TextCtrlPriceObserver\n";
}

void TextCtrlPriceObserver::newPriceCallback(float price) {
    //std::cout << "Price Observerd for Text Ctrl: " << price << std::endl;
    textCtrl->Clear();
    *textCtrl << price;
}

