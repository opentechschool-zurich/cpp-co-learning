#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/app.h"
#include "BasicDrawPane.h"
#include "Definitions.h"

/**
 * Defines a wxDidgets application
 */
class FireworksApp : public wxApp {
    bool OnInit();
};

IMPLEMENT_APP(FireworksApp)

bool FireworksApp::OnInit() {
    wxFrame *frame = new wxFrame((wxFrame *) NULL, -1, wxT("Fireworks"), wxPoint(50, 50), wxSize(800, 600));

    BasicDrawPane *drawPane = new BasicDrawPane((wxFrame*) frame);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show();

    return true;
}


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_LEFT_UP(BasicDrawPane::mouseClicked)
EVT_TIMER(TIMER_ID, BasicDrawPane::OnUpdateTimer)
EVT_TIMER(CREATE_TIMER_ID, BasicDrawPane::OnCreateTimer)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()



