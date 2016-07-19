#pragma once

#include <wx/textctrl.h>
#include "PriceObserver.h"

/**
* Inherits from PriceObserver and updates the wxTextCtrl passed into the
* constructor with any price received
*/
class TextCtrlPriceObserver : public PriceObserver {
private:
    wxTextCtrl* textCtrl;

public:
    TextCtrlPriceObserver(wxTextCtrl* myTextCtrl);
    virtual void newPriceCallback(float price);
};
