#pragma once

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>

#include "wx/chart.h"


/**
* The widget that draws the chart
*/
class XYChart {
public:
	XYChart() {}

	virtual Chart *Create();
};
