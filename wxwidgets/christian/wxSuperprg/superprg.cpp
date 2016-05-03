#include "wx/wx.h"
#include "superprg.h"
#include "mondrian.xpm"


// Event table for MyFrame
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU( Menu_File_Quit, MyFrame::OnQuit )
  EVT_MENU( Menu_File_About, MyFrame::OnAbout )
  EVT_SIZE( MyFrame::OnSize )
  EVT_MOUSE_EVENTS( MyFrame::OnMouseEvent )
  EVT_PAINT( MyFrame::OnPaint )
  EVT_BUTTON( NEIN_ID, MyFrame::OnQuit )

  END_EVENT_TABLE()

  MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
                                    : wxFrame((wxFrame *)0, -1, title, pos, size) {
  // Set the frame icon
  SetIcon(wxIcon(mondrian_xpm));

  // Create a file menu
  wxMenu* fileMenu = new wxMenu;

  fileMenu->Append( Menu_File_About, wxT("&Über ..."));
  fileMenu->AppendSeparator();
  fileMenu->Append( Menu_File_Quit, wxT("&Beenden")); 


  // Now append the freshly created menu to the menu bar...
  wxMenuBar* menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, wxT("&Datei"));

  // ... and attach this menu bar to the frame
  SetMenuBar(menuBar);

  // Create a status bar just for fun
  CreateStatusBar();

  SetStatusText(wxT("Das Superprogramm."));

  NeinButton = new wxButton;
  NeinButton->Create(this, NEIN_ID, wxT("Nein danke."));
  JaButton = new wxButton(this, 1, wxT("Ja!"));
}

void MyFrame::OnAbout(wxCommandEvent& event) {
  wxString msg;
  msg.Printf(wxT("Hello and welcome to %s"),
             wxVERSION_STRING);

  wxMessageBox(msg, wxT("Ein schönes Programm."),
               wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& event) {
  // Destroy the frame
  Close();
}

void MyFrame::OnSize(wxSizeEvent& event) {
#ifndef __unix__                                
  static bool erst = true;                      
  if (erst) erst = false; return;
#endif                                          

  JaButton->SetSize(button_x_pos, button_y_pos, button_width, button_height);
  NeinButton->SetSize(button_x_pos+button_width+button_dist, button_y_pos, button_width, button_height); 

}

void MyFrame::OnPaint(wxPaintEvent& event){
  wxPaintDC dc(this);
  dc.DrawText(wxT("Das Superprogramm starten?"), button_x_pos, button_y_pos/2); 
  }

void MyFrame::OnMouseEvent(wxMouseEvent& event){
  int ButX = button_x_pos;
  wxClientDC dc(this);
  wxPoint pt(event.GetLogicalPosition(dc));
  int xpos = pt.x;
  int ypos = pt.y;
  if (abs(ButX-xpos) < button_width+button_dist){
    ButX +=2*button_width+2*button_dist;
  }
  pt.x = ButX;
  pt.y = button_y_pos;
  JaButton->SetSize(ButX, button_y_pos, button_width, button_height); 

}
