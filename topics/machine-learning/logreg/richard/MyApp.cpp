#include "MyFrame.h"

/**
 * The main class for the wxWidgets application
 */
class MyApp: public wxApp {
    bool OnInit();

    wxFrame *myFrame;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
    myFrame = new MyFrame((wxFrame *)NULL, -1,  wxT("Linear Regression Plot"));
    myFrame->SetAutoLayout(true);
    myFrame->Show();

    return true;
}


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
END_EVENT_TABLE()
