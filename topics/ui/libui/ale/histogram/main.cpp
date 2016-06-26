#include "libui/ui.h"
#include <iostream>
#include <system_error>
#include <string>
#include <random>
#include <functional>
#include <vector>

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

struct Color {
    static const int white{0xFFFFFF};
    static const int black{0x000000};
    static const int dodgerBlue{0x1E90FF};
};

/**
 * TODO: where should this go?
 * it's used by both the toolbox and the drawing area
 */
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

class ToolboxWidget
{
public:
    ToolboxWidget();
    ~ToolboxWidget() {}
    void attach(uiBox* layout);
    void addDatapointChangedAction(std::function<void()> action) {
        datapointChangedActions.push_back(action);
    }
    void addColorChangedAction(std::function<void()> action) {
        colorChangedActions.push_back(action);
    }
private:
    uiBox* toolbox;

    int a = 67;
    vector<int> abc = {1, 2, 3};
    vector<std::function<void()>> datapointChangedActions;
    vector<std::function<void()>> colorChangedActions;
    void onDatapointChanged(uiSpinbox *s, void *data);
    void onColorChanged(uiColorButton *b, void *data);
};

ToolboxWidget::ToolboxWidget()
{
	toolbox = uiNewVerticalBox();
	uiBoxSetPadded(toolbox, 1);

	typedef void (*callback_handlerdatapointchanged_t)(uiSpinbox*, void*);
    Callback<void(uiSpinbox*, void*)>::func = std::bind(&ToolboxWidget::onDatapointChanged, this, std::placeholders::_1, std::placeholders::_2);
    callback_handlerdatapointchanged_t handlerOndatapointchangedFunction = static_cast<callback_handlerdatapointchanged_t>(Callback<void(uiSpinbox*, void*)>::callback);      

	typedef void (*callback_handlercolorchanged_t)(uiColorButton*, void*);
    Callback<void(uiColorButton*, void*)>::func = std::bind(&ToolboxWidget::onColorChanged, this, std::placeholders::_1, std::placeholders::_2);
    callback_handlercolorchanged_t handlerOncolorchangedFunction = static_cast<callback_handlercolorchanged_t>(Callback<void(uiColorButton*, void*)>::callback);      


	// for a random number you need a seeder, an engine and a distribution
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(0, 100);

    // TODO: we will have to figure out a way for the graph to
    // find out the values of the datapoints... we might want to
    // store them in Histogram...
    uiSpinbox *datapoints[10];
	for (int i = 0; i < 10; i++) {
		datapoints[i] = uiNewSpinbox(0, 100);
		uiSpinboxSetValue(datapoints[i], dist(engine));
		uiSpinboxOnChanged(datapoints[i], handlerOndatapointchangedFunction, NULL);
		uiBoxAppend(toolbox, uiControl(datapoints[i]), 0);
	}

    // TODO: we will have to figure out a way for the graph to
    // find out which color is selected... we might want to
    // store it in Histogram...
    uiColorButton *colorButton = uiNewColorButton();
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

void ToolboxWidget::attach(uiBox* layout)
{
	uiBoxAppend(layout, uiControl(toolbox), 0);
}

void ToolboxWidget::onDatapointChanged(uiSpinbox *s, void *data)
{
    for(auto action : datapointChangedActions)
        action();
	// uiAreaQueueRedrawAll(histogram);
}

void ToolboxWidget::onColorChanged(uiColorButton *b, void *data)
{
    for(auto action : colorChangedActions)
        action();
	// uiAreaQueueRedrawAll(histogram);
}


class HistogramWidget
{
public:
    HistogramWidget(uiAreaHandler& handler);
    ~HistogramWidget() {}
    void attach(uiBox* layout);
    void attachController(ToolboxWidget& toolbox);
private:
    uiAreaHandler handler;
    uiArea* histogram;
};

HistogramWidget::HistogramWidget(uiAreaHandler& handler)
: handler{handler}
{
	histogram = uiNewArea(&handler);
}

void HistogramWidget::attach(uiBox* layout)
{
	uiBoxAppend(layout, uiControl(histogram), 1);
}

void HistogramWidget::attachController(ToolboxWidget& toolbox)
{
	// uiAreaQueueRedrawAll(histogram);
    // auto datapointLambda = [this]() { uiAreaQueueRedrawAll(histogram); };
    // toolbox.addDatapointChangedAction(datapointLambda);
    // toolbox.addColorChangedAction();
}

class Window
{
public:
    Window(string title);
    ~Window();
    void create();
    void show();
private:
    string title;
    uiWindow *mainwin;

    uiAreaHandler handler;
	void handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p);
    void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e);
};

Window::Window(string title)
: title{title}
{
}

Window::~Window()
{
    uiControlDestroy(uiControl(mainwin));
}

void Window::create()
{
    // we cannot create mainwin in the constructor, since it needs 
    // gtk to be initialized (uiInitOptions())...
    // so we have to wait, that Histogram has finished its initialisation.
    // ... but, maybe, there is a better solution...
    mainwin = uiNewWindow(title.c_str(), 640, 480, 0);
	uiWindowSetMargined(mainwin, 1);

    uiWindowOnClosing(mainwin, [](uiWindow *w, void *data) {uiControlDestroy(uiControl(w)); uiQuit(); return 0;}, NULL);

	typedef void (*callback_handlerdraw_t)(uiAreaHandler*, uiArea*, uiAreaDrawParams*);
    Callback<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)>::func = std::bind(&Window::handlerDraw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callback_handlerdraw_t handlerDrawFunction = static_cast<callback_handlerdraw_t>(Callback<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)>::callback);      

	typedef void (*callback_handlermouseevent_t)(uiAreaHandler*, uiArea*, uiAreaMouseEvent*);
    Callback<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)>::func = std::bind(&Window::handlerMouseEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callback_handlermouseevent_t handlerMouseeventFunction = static_cast<callback_handlermouseevent_t>(Callback<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)>::callback);      

	handler.Draw = handlerDrawFunction;
	handler.MouseEvent = handlerMouseeventFunction;
	handler.MouseCrossed = [] (uiAreaHandler *ha, uiArea *a, int left) {};
	handler.DragBroken = [] (uiAreaHandler *ah, uiArea *a) {};
	handler.KeyEvent = [] (uiAreaHandler *ah, uiArea *a, uiAreaKeyEvent *e) {return 0;}; // reject all keys

    uiBox* mainLayout = uiNewHorizontalBox();
	uiBoxSetPadded(mainLayout, 1);
	uiWindowSetChild(mainwin, uiControl(mainLayout));

    ToolboxWidget toolbox;
    toolbox.attach(mainLayout);

    // TODO: histogram gets deleted at the end of create()
    // it should probably become a class parameter become
    HistogramWidget histogram(handler);
    histogram.attachController(toolbox);
    histogram.attach(mainLayout);

}

void Window::show()
{
    uiControlShow(uiControl(mainwin));
}

/**
 * we should find a way to add c++ handlers from widget to the handlerDraw()
 */
void Window::handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p)
{
}

/**
 * we should find a way to add c++ handlers from widget to the handlerMouseEvent()
 */
void Window::handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
}

class Histogram
{
public:
    Histogram(string title);
    ~Histogram() {}
    void exec();
private:
    Window window;
    int onQuit(void *data);
};

Histogram::Histogram(string title)
: window{title}
{
    uiInitOptions o = {};

    if (uiInit(&o) != NULL) {
        throw  system_error();
    }

	typedef int (*callback_quitfunction_t)(void*);
    Callback<int(void*)>::func = std::bind(&Histogram::onQuit, this, std::placeholders::_1);
    callback_quitfunction_t quitFunction = static_cast<callback_quitfunction_t>(Callback<int(void*)>::callback);      
    uiOnShouldQuit(quitFunction, NULL);
}
void Histogram::exec()
{
    window.create();
    window.show();
    uiMain();
}

int Histogram::onQuit(void *data)
{
    return 1;
}

int main()
{
    Histogram histogram{"libui Histogram Example"};
    histogram.exec();
}
