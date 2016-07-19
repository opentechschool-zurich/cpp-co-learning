#include "toolboxWidget.h"
#include "libui/ui.h"
#include "color.h"
#include "callback.h"

/**
 * @brief Create ten spinboxes and the color chooser.
 *
 * Create the widgets and connect them with the callbacks.
 */
ToolboxWidget::ToolboxWidget(Datapoints& d, Color& c)
:   datapoints{d},
    color{c},
    toolbox{uiNewVerticalBox()},
    colorButton{uiNewColorButton()}
{
	uiBoxSetPadded(toolbox, 1);

	typedef void (*callback_handlerdatapointchanged_t)(uiSpinbox*, void*);
    Callback<void(uiSpinbox*, void*)>::func = std::bind(&ToolboxWidget::onDatapointChanged, this, std::placeholders::_1, std::placeholders::_2);
    callback_handlerdatapointchanged_t handlerOndatapointchangedFunction = static_cast<callback_handlerdatapointchanged_t>(Callback<void(uiSpinbox*, void*)>::callback);      

	for (int i = 0; i < 10; i++) {
		spinbox[i] = {uiNewSpinbox(0, 100), i};
		uiSpinboxSetValue(spinbox[i].spinbox, datapoints.get(i));
		uiSpinboxOnChanged(spinbox[i].spinbox, handlerOndatapointchangedFunction, &(spinbox[i]));
		uiBoxAppend(toolbox, uiControl(spinbox[i].spinbox), 0);
	}

	typedef void (*callback_handlercolorchanged_t)(uiColorButton*, void*);
    Callback<void(uiColorButton*, void*)>::func = std::bind(&ToolboxWidget::onColorChanged, this, std::placeholders::_1, std::placeholders::_2);
    callback_handlercolorchanged_t handlerOncolorchangedFunction = static_cast<callback_handlercolorchanged_t>(Callback<void(uiColorButton*, void*)>::callback);      

    // TODO: we will have to figure out a way for the graph to
    // find out which color is selected... we might want to
    // store it in Histogram... or rather in Color
	uiDrawBrush brush;
	Color::setSolidBrush(&brush, Color::dodgerBlue, 1.0);
	uiColorButtonSetColor(colorButton,
		brush.R,
		brush.G,
		brush.B,
		brush.A);
	uiColorButtonOnChanged(colorButton, handlerOncolorchangedFunction , NULL);
    color.setCurrentBrush(brush);
	uiBoxAppend(toolbox, uiControl(colorButton), 0);
}

/**
 * @brief attach the widget to the parent layout.
 *
 * Window is letting the widget attach itself to the parent layout.
 */
void ToolboxWidget::attach(uiBox* layout)
{
	uiBoxAppend(layout, uiControl(toolbox), 0);
}

/**
 * @brief Update the datapoint value and trigger the callbacks.
 */
void ToolboxWidget::onDatapointChanged(uiSpinbox *s, void *data)
{
    ToolboxWidgetSpinbox* spinbox = static_cast<ToolboxWidgetSpinbox*>(data);
    // std::cout << spinbox->i << std::endl;
    datapoints.set(spinbox->i, uiSpinboxValue(s));
    for(auto action : datapointChangedActions)
        action();
}

/**
 * @brief (Update the color value and) trigger the callbacks.
 */
void ToolboxWidget::onColorChanged(uiColorButton *button, void *data)
{
	double r, g, b, a;
	uiColorButtonColor(button, &r, &g, &b, &a);
    color.setCurrentBrush(r, g, b , a);
    for(auto action : colorChangedActions)
        action();
}
