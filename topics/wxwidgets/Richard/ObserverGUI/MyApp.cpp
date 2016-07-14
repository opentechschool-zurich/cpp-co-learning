#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/app.h"
#include "Definitions.h"
#include "MyFrame.h"

/**
 * Defines a wxDidgets application
 */
class MyApp: public wxApp {
    bool OnInit();

    wxFrame *myFrame;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
    myFrame = new MyFrame((wxFrame *)NULL, -1,  wxT("myFrame"), wxPoint(50,50), wxSize(800,600));
    myFrame->SetAutoLayout(true);
    myFrame->Show();

    return true;
}


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
//EVT_LEFT_UP(BasicDrawPane::mouseClicked)
EVT_TIMER(TIMER_ID, MyFrame::OnTimer)
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
//EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()
