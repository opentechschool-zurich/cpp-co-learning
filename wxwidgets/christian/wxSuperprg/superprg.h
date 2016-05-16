#pragma once


// Declare the application class
class MyApp : public wxApp
{
    public:
        // Called on application startup
        virtual bool OnInit() override;
};



// Declare our main frame class
class MyFrame : public wxFrame
{
 public:
  // Constructor
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size
          );

  // Event handlers
  void OnQuit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnPaint(wxPaintEvent& event);
  void OnMouseEvent(wxMouseEvent& event);
        
        
 private:
  wxButton *JaButton, *NeinButton;


  DECLARE_EVENT_TABLE()
    };

enum{
  Menu_File_Quit = 100, Menu_File_About};

