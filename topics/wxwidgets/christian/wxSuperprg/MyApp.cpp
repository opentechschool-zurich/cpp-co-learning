#include "wx/wx.h"
#include "superprg.h"

// selbstgeschnitzte Konstanten
constexpr int NEIN_ID       = 5;
constexpr int JA_ID         = 4;
constexpr int button_x_pos  = 50;
constexpr int button_y_pos  = 100;
constexpr int button_width  = 120;
constexpr int button_dist   = 50;
constexpr int button_height = 30;



// Implements MyApp& wxGetApp()
DECLARE_APP(MyApp)

// Give wxWidgets the means to create a MyApp object
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    // Create the main application window
  MyFrame* frame = new MyFrame(wxT("Das Superprogramm"),
                               wxPoint(50,50), wxSize(3*button_width + 4*button_dist, 340));
    
  // Show it
  frame->Show(true);
  SetTopWindow(frame);
  // Start the event loop
  return true;
}
