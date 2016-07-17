#pragma once
#include <wx/timer.h>
#include "PricePublisher.h"
#include "MyFrame_generated.h"
#include "Definitions.h"

class MyFrame : public MyFrame_generated {
private:
    PricePublisher pricePublisher;

protected:
    wxTimer m_timer;

public:

    MyFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(725, 337), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL)
    : MyFrame_generated(parent, id, title, pos, size, style)
    , m_timer(this, TIMER_ID) {

    }

    void OnTimer(wxTimerEvent& event);
    DECLARE_EVENT_TABLE()

    void onStartButtonClicked(wxCommandEvent& event) override;
    void onAddPriceObserverClicked(wxCommandEvent& event) override;
    void onAddHighObserverClicked(wxCommandEvent& event) override;
    void onAddLowObserverClicked(wxCommandEvent& event) override;
    void onAddAverageObserverClicked(wxCommandEvent& event) override;

};

