#include "MyFrame.h"
#include "TextCtrlPriceObserver.h"
#include "HighPriceObserver.h"
#include "LowPriceObserver.h"
#include "AvgPriceObserver.h"




void MyFrame::onStartButtonClicked(wxCommandEvent& event) {
    m_timer.Start(400); //ms
}

void MyFrame::onAddPriceObserverClicked(wxCommandEvent& event) {
    //std::cout << "Add Price Observer clicked!\n";
    TextCtrlPriceObserver *tcpo = new TextCtrlPriceObserver{m_textCtrlPrice};
    pricePublisher.registerPriceObserver(tcpo);
}

void MyFrame::onAddHighObserverClicked(wxCommandEvent& event) {
    HighPriceObserver *o = new HighPriceObserver{m_textCtrlHigh};
    pricePublisher.registerPriceObserver(o);
}

void MyFrame::onAddLowObserverClicked(wxCommandEvent& event) {
    LowPriceObserver *o = new LowPriceObserver{m_textCtrlLow};
    pricePublisher.registerPriceObserver(o);
}

void MyFrame::onAddAverageObserverClicked(wxCommandEvent& event) {
    AvgPriceObserver *o = new AvgPriceObserver{m_textCtrlAverage};
    pricePublisher.registerPriceObserver(o);
}


/**
 * This method is called by the wxTimer. We use this event to update the position
 * of all our objects.
 * 
 * @param event The timer event
 */
void MyFrame::OnTimer(wxTimerEvent& event) {
    pricePublisher.publishNextPrice();
}
