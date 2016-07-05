#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include "datapoints.h"
#include "color.h"

class ToolboxWidget;
class Window;
class uiBox;
class uiAreaHandler;
class uiArea;
class uiAreaMouseEvent;
class uiAreaDrawParams;
class uiDrawPath;

/**
 * @brief UI elements and drawing for the main drawing pane
 */
class HistogramWidget
{
    public:
        HistogramWidget(uiAreaHandler& handler, Datapoints& d, Color& c);
        ~HistogramWidget() {}
        /** @brief Attach the datapoints model */
        void attachDatapoints(Datapoints& d) {datapoints = d;}
        /** @brief Attach the colors model */
        void attachColor(Color& c) {color = c;}
        void attach(uiBox* layout);
        void attachToolboxController(ToolboxWidget& toolbox);
        void attachHandlerController(Window* window);
        void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e);
        void handlerDraw(uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p);
    private:
        uiAreaHandler& handler;
        Datapoints& datapoints;
        Color& color;
        uiArea* histogram;

        /* histogram margins */
        const int xoffLeft = 20;
        const int yoffTop = 20;
        const int xoffRight = 20;
        const int yoffBottom = 20;
        const int pointRadius = 5;

        void graphSize(double clientWidth, double clientHeight, double *graphWidth, double *graphHeight);
        uiDrawPath *constructGraph(double width, double height, int extend);

        void pointLocations(double width, double height, double *xs, double *ys);
        /** The point being hovered */
        int currentPoint = -1;
};

#endif
