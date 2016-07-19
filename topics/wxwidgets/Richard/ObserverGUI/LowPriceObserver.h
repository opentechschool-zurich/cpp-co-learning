#pragma once

#include <wx/textctrl.h>
#include "PriceObserver.h"
#include <limits>

/**
* Inherits from PriceObserver and updates the wxTextCtrl passed into the
* constructor with the lowest price received
*/
class LowPriceObserver : public PriceObserver {
private:
    wxTextCtrl* textCtrl;
    float lowWatermark = std::numeric_limits<float>::max();

public:
    LowPriceObserver(wxTextCtrl* myTextCtrl);
    virtual void newPriceCallback(float price);
};
