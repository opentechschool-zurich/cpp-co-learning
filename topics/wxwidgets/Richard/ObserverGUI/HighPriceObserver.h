#pragma once

#include <wx/textctrl.h>
#include "PriceObserver.h"
#include <limits>

class HighPriceObserver : public PriceObserver {
private:
    wxTextCtrl* textCtrl;
    float highWatermark = std::numeric_limits<float>::min();
    
public:
    HighPriceObserver(wxTextCtrl* myTextCtrl);
    virtual void newPriceCallback(float price);
};