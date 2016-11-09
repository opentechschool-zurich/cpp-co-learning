#include "MyFrame.h"
#include "linReg.h"

void MyFrame::onStartButtonClicked(wxCommandEvent &event) {
  m_timer.Start(400); // ms
  doLinearRegression();
}

/**
 * This method is called by the wxTimer. We use this event to update the
 * position
 * of all our objects.
 *
 * @param event The timer event
 */
void MyFrame::OnTimer(wxTimerEvent &event) {
  pricePublisher.publishNextPrice();
}
