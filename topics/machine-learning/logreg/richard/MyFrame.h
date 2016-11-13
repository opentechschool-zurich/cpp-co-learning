#pragma once
#include "src-formbuilder/MyFrame_generated.h"
#include "XYChart.h"
#include <wx/chartpanel.h>

/**
* This is the class for the principle frame of the application
*/
class MyFrame : public MyFrame_generated {
private:
  DECLARE_EVENT_TABLE()

public:
  MyFrame(wxWindow *parent, wxWindowID id = wxID_ANY,
          const wxString &title = wxEmptyString)
      : MyFrame_generated(parent, id, title) {

    XYChart *chart = new XYChart();
    wxChartPanel *m_chartPanel = new wxChartPanel(this, wxID_ANY);
    m_chartPanel->SetChart(chart->Create());

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(m_chartPanel, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(hbox);
  }

};
