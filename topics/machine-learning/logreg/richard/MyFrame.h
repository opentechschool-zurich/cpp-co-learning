#pragma once
#include "Definitions.h"
#include "MyFrame_generated.h"
#include "XYChart.h"

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
    m_chartPanel->SetChart(chart->Create());
  }

};
