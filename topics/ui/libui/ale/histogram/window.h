#ifndef WINDOW_H
#define WINDOW_H

#include<vector>
#include<string>
#include<functional>

#include "libui/ui.h"

#include "toolboxWidget.h"
#include "histogramWidget.h"

class Datapoints;
class Color;

using namespace std;

class Window
{
    public:
        Window(string title);
        ~Window();
        void show();
        void addMouseEventAction(function<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)> action) {
            mouseEventActions.push_back(action);
        }
        void addDrawAction(function<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)> action) {
            drawActions.push_back(action);
        }
    private:
        string title;
        HistogramWidget histogram;

        Datapoints datapoints;
        Color color;

        ToolboxWidget toolbox{datapoints, color};

        vector<function<void(uiAreaHandler*, uiArea*, uiAreaMouseEvent*)>> mouseEventActions;
        vector<function<void(uiAreaHandler*, uiArea*, uiAreaDrawParams*)>> drawActions;

        uiBox* mainLayout;
        uiWindow *mainwin;

        uiAreaHandler handler;
        void handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p);
        void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e);

        int onQuit(void *data) {return 1;}
};

#endif
