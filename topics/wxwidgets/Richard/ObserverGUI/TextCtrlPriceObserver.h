#pragma once

#include <wx/textctrl.h>
#include "PriceObserver.h"

class TextCtrlPriceObserver : public PriceObserver {
private:
    wxTextCtrl* textCtrl;
    
public:
    TextCtrlPriceObserver(wxTextCtrl* myTextCtrl);
    virtual void newPriceCallback(float price);
};