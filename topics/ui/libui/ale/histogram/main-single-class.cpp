#include "libui/ui.h"
#include <system_error>
#include <string>
#include <random>
#include <functional>

using namespace std;

// ----------------------------
// templates for mapping a c++ class method to a function pointer
// http://stackoverflow.com/questions/1000663/using-a-c-class-member-function-as-a-c-callback-function

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args> 
    static Ret callback(Args... args) {                    
        func(args...);  
    }
    static std::function<Ret(Params...)> func; 
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

// end of the mapping templates
// ----------------------------

// this is what we need for the uiOnShouldQuit()

static void setSolidBrush(uiDrawBrush *brush, uint32_t color, double alpha)
{
	uint8_t component;

	brush->Type = uiDrawBrushTypeSolid;
	component = (uint8_t) ((color >> 16) & 0xFF);
	brush->R = ((double) component) / 255;
	component = (uint8_t) ((color >> 8) & 0xFF);
	brush->G = ((double) component) / 255;
	
	brush->B = ((double) component) / 255;
	brush->A = alpha;
}

struct Color {
    static const int white{0xFFFFFF};
    static const int black{0x000000};
    static const int dodgerBlue{0x1E90FF};
};

class Histogram
{
public:
    Histogram();
    ~Histogram() {};
    void setupWindow(string title);
    void setupToolbox();
    void show();
    void exec();

private:
    uiWindow *mainwin;
    uiBox* mainLayout;
    uiBox* toolbox;
    uiArea *histogram;

    uiAreaHandler handler;
	void handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p);
    void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e);
    void onDatapointChanged(uiSpinbox *s, void *data);
    void onColorChanged(uiColorButton *b, void *data);

    uiSpinbox *datapoints[10];
    uiColorButton *colorButton;

    int onQuit(void *data);

    int currentPoint = -1;
    void graphSize(double clientWidth, double clientHeight, double *graphWidth, double *graphHeight);
    uiDrawPath *constructGraph(double width, double height, int extend);
    void pointLocations(double width, double height, double *xs, double *ys);
    int inPoint(double x, double y, double xtest, double ytest);

	/* histogram margins */
    const int xoffLeft = 20;
    const int yoffTop = 20;
    const int xoffRight = 20;
    const int yoffBottom = 20;
    const int pointRadius = 5;

};

Histogram::Histogram()
{
    uiInitOptions o = {};

    if (uiInit(&o) != NULL) {
        throw  system_error();
    }

    // it's not possible to pass capturing lambda as function pointers
    // but we can convert the class method to a function pointer
    // http://stackoverflow.com/questions/7852101/c-lambda-with-captures-as-a-function-pointer
	typedef int (*callback_quitfunction_t)(void*);
    Callback<int(void*)>::func = std::bind(&Histogram::onQuit, this, std::placeholders::_1);
    callback_quitfunction_t quitFunction = static_cast<callback_quitfunction_t>(Callback<int(void*)>::callback);      
    uiOnShouldQuit(quitFunction, NULL);
}

int Histogram::onQuit(void *data)
{
    uiControlDestroy(uiControl(mainwin));
    return 1;
}

void Histogram::handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawBrush brush;
	uiDrawStrokeParams sp;
	uiDrawMatrix m;
	double graphWidth, graphHeight;
	double graphR, graphG, graphB, graphA;

	// fill the area with white
	setSolidBrush(&brush, Color::white, 1.0);
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
	setSolidBrush(&brush, Color::black, 1.0);
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
	uiColorButtonColor(colorButton, &graphR, &graphG, &graphB, &graphA);
	brush.Type = uiDrawBrushTypeSolid;
	brush.R = graphR;
	brush.G = graphG;
	brush.B = graphB;
	// we set brush->A below to different values for the fill and stroke

	// now create the fill for the graph below the graph line
	path = constructGraph(graphWidth, graphHeight, 1);
	brush.A = graphA / 2;
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);

	// now draw the histogram line
	path = constructGraph(graphWidth, graphHeight, 0);
	brush.A = graphA;
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

void Histogram::handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
	double graphWidth, graphHeight;
	double xs[10], ys[10];
	int i;

	graphSize(e->AreaWidth, e->AreaHeight, &graphWidth, &graphHeight);
	pointLocations(graphWidth, graphHeight, xs, ys);

	for (i = 0; i < 10; i++)
		if (inPoint(e->X, e->Y, xs[i], ys[i]))
			break;
	if (i == 10)		// not in a point
		i = -1;

	currentPoint = i;
	// TODO only redraw the relevant area
	uiAreaQueueRedrawAll(histogram);
}

void Histogram::onDatapointChanged(uiSpinbox *s, void *data)
{
	uiAreaQueueRedrawAll(histogram);
}

void Histogram::onColorChanged(uiColorButton *b, void *data)
{
	uiAreaQueueRedrawAll(histogram);
}

void Histogram::setupWindow(string title)
{
	mainwin = uiNewWindow(title.c_str(), 640, 480, 0);
	uiWindowSetMargined(mainwin, 1);

    // in main.c it destrois the global mainwin, instead of w
    // if that's correct, we should also use the template to convert
    // to bind the class method to a function pointer
    uiWindowOnClosing(mainwin, [](uiWindow *w, void *data) {uiControlDestroy(uiControl(w)); uiQuit(); return 0;}, NULL);

	mainLayout = uiNewHorizontalBox();
	uiBoxSetPadded(mainLayout, 1);
	uiWindowSetChild(mainwin, uiControl(mainLayout));

	toolbox = uiNewVerticalBox();
	uiBoxSetPadded(toolbox, 1);
	uiBoxAppend(mainLayout, uiControl(toolbox), 0);

	typedef void (*callback_handlerdraw_t)(uiAreaHandler*, uiArea*, uiAreaDrawParams*);
    Callback<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)>::func = std::bind(&Histogram::handlerDraw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callback_handlerdraw_t handlerDrawFunction = static_cast<callback_handlerdraw_t>(Callback<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)>::callback);      

	typedef void (*callback_handlermouseevent_t)(uiAreaHandler*, uiArea*, uiAreaMouseEvent*);
    Callback<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)>::func = std::bind(&Histogram::handlerMouseEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callback_handlermouseevent_t handlerMouseeventFunction = static_cast<callback_handlermouseevent_t>(Callback<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)>::callback);      

	handler.Draw = handlerDrawFunction;

	handler.MouseEvent = handlerMouseeventFunction;
	handler.MouseCrossed = [] (uiAreaHandler *ha, uiArea *a, int left) {};
	handler.DragBroken = [] (uiAreaHandler *ah, uiArea *a) {};
	handler.KeyEvent = [] (uiAreaHandler *ah, uiArea *a, uiAreaKeyEvent *e) {return 0;}; // reject all keys

	histogram = uiNewArea(&handler);
	uiBoxAppend(mainLayout, uiControl(histogram), 1);
}

void Histogram::graphSize(double clientWidth, double clientHeight, double *graphWidth, double *graphHeight)
{
	*graphWidth = clientWidth - xoffLeft - xoffRight;
	*graphHeight = clientHeight - yoffTop - yoffBottom;
}

uiDrawPath* Histogram::constructGraph(double width, double height, int extend)
{
	uiDrawPath *path;
	double xs[10], ys[10];
	int i;

	pointLocations(width, height, xs, ys);

	path = uiDrawNewPath(uiDrawFillModeWinding);

	uiDrawPathNewFigure(path, xs[0], ys[0]);
	for (i = 1; i < 10; i++)
		uiDrawPathLineTo(path, xs[i], ys[i]);

	if (extend) {
		uiDrawPathLineTo(path, width, height);
		uiDrawPathLineTo(path, 0, height);
		uiDrawPathCloseFigure(path);
	}

	uiDrawPathEnd(path);
	return path;
}

void Histogram::pointLocations(double width, double height, double *xs, double *ys)
{
	double xincr, yincr;
	int i, n;

	xincr = width / 9;		// 10 - 1 to make the last point be at the end
	yincr = height / 100;

	for (i = 0; i < 10; i++) {
		// get the value of the point
		n = uiSpinboxValue(datapoints[i]);
		// because y=0 is the top but n=0 is the bottom, we need to flip
		n = 100 - n;
		xs[i] = xincr * i;
		ys[i] = yincr * n;
	}
}

int Histogram::inPoint(double x, double y, double xtest, double ytest)
{
	// TODO switch to using a matrix
	x -= xoffLeft;
	y -= yoffTop;
	return (x >= xtest - pointRadius) &&
		(x <= xtest + pointRadius) &&
		(y >= ytest - pointRadius) &&
		(y <= ytest + pointRadius);
}

void Histogram::setupToolbox()
{

	typedef void (*callback_handlerdatapointchanged_t)(uiSpinbox*, void*);
    Callback<void(uiSpinbox*, void*)>::func = std::bind(&Histogram::onDatapointChanged, this, std::placeholders::_1, std::placeholders::_2);
    callback_handlerdatapointchanged_t handlerOndatapointchangedFunction = static_cast<callback_handlerdatapointchanged_t>(Callback<void(uiSpinbox*, void*)>::callback);      

	typedef void (*callback_handlercolorchanged_t)(uiColorButton*, void*);
    Callback<void(uiColorButton*, void*)>::func = std::bind(&Histogram::onColorChanged, this, std::placeholders::_1, std::placeholders::_2);
    callback_handlercolorchanged_t handlerOncolorchangedFunction = static_cast<callback_handlercolorchanged_t>(Callback<void(uiColorButton*, void*)>::callback);      


	// for a random number you need a seeder, an engine and a distribution
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(0, 100);

	for (int i = 0; i < 10; i++) {
		datapoints[i] = uiNewSpinbox(0, 100);
		uiSpinboxSetValue(datapoints[i], dist(engine));
		uiSpinboxOnChanged(datapoints[i], handlerOndatapointchangedFunction, NULL);
		uiBoxAppend(toolbox, uiControl(datapoints[i]), 0);
	}

	colorButton = uiNewColorButton();
	uiDrawBrush brush;
	setSolidBrush(&brush, Color::dodgerBlue, 1.0);
	uiColorButtonSetColor(colorButton,
		brush.R,
		brush.G,
		brush.B,
		brush.A);
	uiColorButtonOnChanged(colorButton, handlerOncolorchangedFunction , NULL);
	uiBoxAppend(toolbox, uiControl(colorButton), 0);
}

void Histogram::show()
{
    uiControlShow(uiControl(mainwin));
}

void Histogram::exec()
{
    uiMain();
}


int main()
{
    Histogram histogram{};
    histogram.setupWindow("libui Histogram Example");
    histogram.setupToolbox();
    histogram.show();
    histogram.exec();
}
