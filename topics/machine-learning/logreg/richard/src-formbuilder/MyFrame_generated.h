///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov  9 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MYFRAME_GENERATED_H__
#define __MYFRAME_GENERATED_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class wxChartPanel;

#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame_generated
///////////////////////////////////////////////////////////////////////////////
class MyFrame_generated : public wxFrame 
{
	private:
	
	protected:
		wxButton* m_startButton;
		wxChartPanel* m_chartPanel;
		wxStatusBar* m_statusBar1;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onStartButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyFrame_generated( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 690,434 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame_generated();
	
};

#endif //__MYFRAME_GENERATED_H__
