#include "histogramWidget.h"
#include <iostream>
#include "toolboxWidget.h"
#include "window.h"
#include "color.h"

#include <iostream>

using namespace std;

HistogramWidget::HistogramWidget(uiAreaHandler& handler, Datapoints& d, Color& c)
: handler(handler),
  datapoints(d),
  color(c),
  histogram{uiNewArea(&handler)}
{
}

/**
 * @brief attach the widget to the parent layout.
 *
 * Window is letting the widget attach itself to the parent layout.
 */
void HistogramWidget::attach(uiBox* layout)
{
	uiBoxAppend(layout, uiControl(histogram), 1);
}

/**
 * @brief Attach the histogram's changed action to the toolbox widget.
 *
 * @todo:
 * - we probably want to move the changed action to Datapoints instead
 *   of Toolbox.
 */
void HistogramWidget::attachToolboxController(ToolboxWidget& toolbox)
{
    auto datapointLambda = [this]() {uiAreaQueueRedrawAll(histogram);};
    toolbox.addDatapointChangedAction(datapointLambda);
    auto colorLambda = [this]() {uiAreaQueueRedrawAll(histogram);};
    toolbox.addColorChangedAction(colorLambda);
}

void HistogramWidget::handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
}

void HistogramWidget::handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawBrush brush;
	uiDrawStrokeParams sp;
	uiDrawMatrix m;
	double graphWidth, graphHeight;

	// fill the area with white
	Color::setSolidBrush(&brush, Color::white, 1.0);
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, 0, 0, p->AreaWidth, p->AreaHeight);
	uiDrawPathEnd(path);
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);

	// figure out dimensions
	graphSize(p->AreaWidth, p->AreaHeight, &graphWidth, &graphHeight);

	// clear sp to avoid passing garbage to uiDrawStroke()
	// for example, we don't use dashing
	// memset(&sp, 0, sizeof (uiDrawStrokeParams));
    sp = {};

	// make a stroke for both the axes and the histogram line
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.Thickness = 2;
	sp.MiterLimit = uiDrawDefaultMiterLimit;

	// draw the axes
	Color::setSolidBrush(&brush, Color::black, 1.0);
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path,
		xoffLeft, yoffTop);
	uiDrawPathLineTo(path,
		xoffLeft, yoffTop + graphHeight);
	uiDrawPathLineTo(path,
		xoffLeft + graphWidth, yoffTop + graphHeight);
	uiDrawPathEnd(path);
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	// now transform the coordinate space so (0, 0) is the top-left corner of the graph
	uiDrawMatrixSetIdentity(&m);
	uiDrawMatrixTranslate(&m, xoffLeft, yoffTop);
	uiDrawTransform(p->Context, &m);

	// now get the color for the graph itself and set up the brush
    brush = color.getCurrentBrush();
	// we set brush->A below to different values for the fill and stroke

	// now create the fill for the graph below the graph line
	path = constructGraph(graphWidth, graphHeight, 1);
	brush.A = brush.A / 2;
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);

	// now draw the histogram line
	path = constructGraph(graphWidth, graphHeight, 0);
	brush.A = brush.A * 2; // TODO: check if we can do better... initial A is 1 anyway
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	// now draw the point being hovered over
	if (currentPoint != -1) {
		double xs[10], ys[10];

		pointLocations(graphWidth, graphHeight, xs, ys);
		path = uiDrawNewPath(uiDrawFillModeWinding);
		uiDrawPathNewFigureWithArc(path,
			xs[currentPoint], ys[currentPoint],
			pointRadius,
			0, 6.23,		// TODO pi
			0);
		uiDrawPathEnd(path);
		// use the same brush as for the histogram lines
		uiDrawFill(p->Context, path, &brush);
		uiDrawFreePath(path);
	}
}

void HistogramWidget::attachHandlerController(Window* window)
{
    auto mouseEventLambda = [this](uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e) {handlerMouseEvent(a, area, e);};
    window->addMouseEventAction(mouseEventLambda);

    auto drawLambda = [this](uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p) {handlerDraw(ah, a, p);};
    window->addDrawAction(drawLambda);
}

void HistogramWidget::graphSize(double clientWidth, double clientHeight, double *graphWidth, double *graphHeight)
{
	*graphWidth = clientWidth - xoffLeft - xoffRight;
	*graphHeight = clientHeight - yoffTop - yoffBottom;
}

uiDrawPath* HistogramWidget::constructGraph(double width, double height, int extend)
{
	uiDrawPath *path;
	double xs[10], ys[10];
	int i;

	pointLocations(width, height, xs, ys);

	path = uiDrawNewPath(uiDrawFillModeWinding);

	uiDrawPathNewFigure(path, xs[0], ys[0]);
	for (i = 1; i < 10; i++) {
        // std::cout << "xs[" << i <<"] : " << xs[i] << std::endl;
        // std::cout << "ys[" << i <<"] : " << ys[i] << std::endl;
		uiDrawPathLineTo(path, xs[i], ys[i]);
    }

	if (extend) {
		uiDrawPathLineTo(path, width, height);
		uiDrawPathLineTo(path, 0, height);
		uiDrawPathCloseFigure(path);
	}

	uiDrawPathEnd(path);
	return path;
}

void HistogramWidget::pointLocations(double width, double height, double *xs, double *ys)
{
	double xincr, yincr;
	int i, n;

	xincr = width / 9;		// 10 - 1 to make the last point be at the end
	yincr = height / 100;

    // std::cout << "datapoints.size " << datapoints.size() << std::endl;
	for (i = 0; i < 10; i++) {
		// get the value of the point
		n = datapoints.get(i);
        // std::cout << "n[" << i <<"] : " << n << std::endl;
		// because y=0 is the top but n=0 is the bottom, we need to flip
		n = 100 - n;
		xs[i] = xincr * i;
		ys[i] = yincr * n;
	}
}
