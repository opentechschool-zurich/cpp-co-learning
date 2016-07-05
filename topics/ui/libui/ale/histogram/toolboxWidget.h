#ifndef TOOLBOXWIDGET_H
#define TOOLBOXWIDGET_H

#include <functional>
#include <vector>
#include "datapoints.h"
#include "color.h"
class uiBox;
class uiSpinbox;
class uiColorButton;

class Datapoints;
class Color;

using namespace std;

/**
 * @brief Encapsulate the Spinbox and the index in a struct.
 *
 * We cannot pass an int as `void *data` to uiSpinboxOnChanged.
 * We need to store it in a struct that is kept in memory as long the
 * widget is alive.
 * 
 */
struct ToolboxWidgetSpinbox
{

    uiSpinbox *spinbox;
    int i;
};

/**
 * @brief The UI elements for the left panel
 */
class ToolboxWidget
{
    public:
        ToolboxWidget(Datapoints& d, Color& c);
        ~ToolboxWidget() {}
        /** @brief Attach the datapoints model */
        // void attachDatapoints(Datapoints& d) {datapoints = d;}
        /** @brief Attach the colors model */
        // void attachColor(Color& c) {color = c;}
        void attach(uiBox* layout);
        /**
         * @brief Attach the spinbox callbacks
         * @param action The function to be called when the spinbox changes
         * @todo:
         * - It might be better to move this action to the Datapoint structure.
         */
        void addDatapointChangedAction(function<void(void)> action) {
            datapointChangedActions.push_back(action);
        }
        void addColorChangedAction(function<void(void)> action) {
            colorChangedActions.push_back(action);
        }
    private:
        Datapoints& datapoints;
        Color& color;
        uiBox* toolbox;
        ToolboxWidgetSpinbox spinbox[10];

        void onDatapointChanged(uiSpinbox *s, void *data);
        vector<function<void(void)>> datapointChangedActions;

        uiColorButton *colorButton;

        vector<function<void()>> colorChangedActions;
        void onColorChanged(uiColorButton *b, void *data);

};
#endif
