#pragma once

#include <wx/textctrl.h>
#include "PriceObserver.h"
#include <limits>

class AvgPriceObserver : public PriceObserver {
private:
    wxTextCtrl* textCtrl;
    float sum = 0.0;
    int counter = 0;
    
public:
    AvgPriceObserver(wxTextCtrl* myTextCtrl);
    virtual void newPriceCallback(float price);
};