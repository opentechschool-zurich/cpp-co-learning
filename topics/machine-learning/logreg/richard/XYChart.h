#pragma once

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>
//#include <wx/axis/logarithmicnumberaxis.h>

// for histogram demo
#include <wx/xy/xyhistorenderer.h>

// for area demo
#include <wx/xy/xyarearenderer.h>


#include <wx/xy/functions/sinefunction.h>

#include <math.h>
#include "wx/chart.h"



/*BEGIN_EVENT_TABLE(DynamicDemoDatasetUpdater, wxEvtHandler)
	EVT_TIMER(wxID_ANY, DynamicDemoDatasetUpdater::OnTimer)
END_EVENT_TABLE()*/

/**
* The widget that draws the chart
*/
class XYChart {
public:
	XYChart() {}

	virtual Chart *Create();
};
