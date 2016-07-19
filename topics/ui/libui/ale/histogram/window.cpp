#include "window.h"
#include "callback.h"
#include "datapoints.h"
#include "color.h"
#include <vector>

Window::Window(string title)
: title{title},
  mainLayout{uiNewHorizontalBox()},
  histogram(handler, datapoints, color)
{
    mainwin = uiNewWindow(title.c_str(), 640, 480, 0);
	uiWindowSetMargined(mainwin, 1);

	uiBoxSetPadded(mainLayout, 1);
	uiWindowSetChild(mainwin, uiControl(mainLayout));

	typedef void (*callback_handlerdraw_t)(uiAreaHandler*, uiArea*, uiAreaDrawParams*);
    Callback<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)>::func = std::bind(&Window::handlerDraw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callback_handlerdraw_t handlerDrawFunction = static_cast<callback_handlerdraw_t>(Callback<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)>::callback);      

	typedef void (*callback_handlermouseevent_t)(uiAreaHandler*, uiArea*, uiAreaMouseEvent*);
    Callback<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)>::func = std::bind(&Window::handlerMouseEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callback_handlermouseevent_t handlerMouseeventFunction = static_cast<callback_handlermouseevent_t>(Callback<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)>::callback);      

    // only draw and mouseEvent are implemented for now
    // they are "filled" by the widgets
	handler.Draw = handlerDrawFunction;
	handler.MouseEvent = handlerMouseeventFunction;
	handler.MouseCrossed = [] (uiAreaHandler *ha, uiArea *a, int left) {};
	handler.DragBroken = [] (uiAreaHandler *ah, uiArea *a) {};
	handler.KeyEvent = [] (uiAreaHandler *ah, uiArea *a, uiAreaKeyEvent *e) {return 0;}; // reject all keys

    // todo: the data should be stored in the histogramm application,
    // not in the window
    // TODO: the datapoints and color are not passed correctly by reference!
    toolbox.attach(mainLayout);

    histogram.attachToolboxController(toolbox);
    histogram.attachHandlerController(this);
    histogram.attach(mainLayout);

    uiWindowOnClosing(mainwin, [](uiWindow *w, void *data) {uiControlDestroy(uiControl(w)); uiQuit(); return 0;}, NULL);

	typedef int (*callback_quitfunction_t)(void*);
    Callback<int(void*)>::func = std::bind(&Window::onQuit, this, std::placeholders::_1);
    callback_quitfunction_t quitFunction = static_cast<callback_quitfunction_t>(Callback<int(void*)>::callback);      
    uiOnShouldQuit(quitFunction, NULL);
}

Window::~Window()
{
    uiControlDestroy(uiControl(mainwin));
}

void Window::show()
{
    uiControlShow(uiControl(mainwin));
}

/**
 * @todo:
 * - we should find a way to add c++ handlers from widget to the handlerDraw()
 */
void Window::handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p)
{
    for(auto action : drawActions)
        action(ah, a, p);
}

/**
 * @todo:
 * - we should find a way to add c++ handlers from widget to the handlerMouseEvent()
 */
void Window::handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
    for(auto action : mouseEventActions)
        action(a, area, e);
}

