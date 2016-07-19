#pragma once

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/axis/logarithmicnumberaxis.h>

// for histogram demo
#include <wx/xy/xyhistorenderer.h>

// for area demo
#include <wx/xy/xyarearenderer.h>

// for dynamic dataset
#include <wx/xy/vectordataset.h>

#include <wx/xy/functions/sinefunction.h>

#include <math.h>
#include "PriceObserver.h"
#include "wx/chart.h"

class DynamicDemoDatasetUpdater;

/**
 * Dataset for the chart.
 */
class DynamicDemoDataset : public VectorDataset
{
public:
	DynamicDemoDataset();
	virtual ~DynamicDemoDataset();

private:
	DynamicDemoDatasetUpdater *m_updater;
};

/**
 * Class, that updates dynamic dataset on timer.
 */
class DynamicDemoDatasetUpdater : public wxEvtHandler
{
public:
	DynamicDemoDatasetUpdater(DynamicDemoDataset *dataset);
	virtual ~DynamicDemoDatasetUpdater();

private:

	wxTimer m_timer;

	void OnTimer(wxTimerEvent &ev);

	//DECLARE_EVENT_TABLE()
};

/*BEGIN_EVENT_TABLE(DynamicDemoDatasetUpdater, wxEvtHandler)
	EVT_TIMER(wxID_ANY, DynamicDemoDatasetUpdater::OnTimer)
END_EVENT_TABLE()*/

/**
* The widget that draws the chart
*/
class XYChart : public PriceObserver  {
public:
	XYChart() {}

	DynamicDemoDataset *m_dataset;

	virtual Chart *Create();
    virtual void newPriceCallback(float price);
};
