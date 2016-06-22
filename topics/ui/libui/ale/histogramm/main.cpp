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
typedef int (*callback_t)(void*);

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

class Histogramm
{
public:
    Histogramm();
    ~Histogramm() {};
    void setupWindow(string title);
    void setupToolbox();
    void show();
    void exec();

    int onQuit(void *data);
private:
    uiWindow *mainwin;
    uiBox* mainLayout;
    uiBox* toolbox;
    uiArea *histogram;

    uiAreaHandler handler;

    uiSpinbox *datapoints[10];
    uiColorButton *colorButton;


};

Histogramm::Histogramm()
{
    uiInitOptions o = {};

    if (uiInit(&o) != NULL) {
        throw  system_error();
    }

    // TODO: does not compile: cannot pass the lambda when capturing
    // http://stackoverflow.com/questions/7852101/c-lambda-with-captures-as-a-function-pointer


    Callback<int(void*)>::func = std::bind(&Histogramm::onQuit, this, std::placeholders::_1);
    callback_t func = static_cast<callback_t>(Callback<int(void*)>::callback);      

    uiOnShouldQuit(func, NULL);
    // uiOnShouldQuit([this](void *data) {uiControlDestroy(uiControl(mainwin)); return 1;}, NULL);
}

int Histogramm::onQuit(void *data)
{
    uiControlDestroy(uiControl(mainwin));
    return 1;
}

void Histogramm::setupWindow(string title)
{
	mainwin = uiNewWindow(title.c_str(), 640, 480, 0);
	uiWindowSetMargined(mainwin, 1);

    Callback<int(void*)>::func = std::bind(&Histogramm::onQuit, this, std::placeholders::_1);
    callback_t func = static_cast<callback_t>(Callback<int(void*)>::callback);      

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

	handler.Draw = [] (uiAreaHandler *ah, uiArea *a, uiAreaDrawParams *p) {};

	handler.MouseEvent = [] (uiAreaHandler *ah, uiArea *a, uiAreaMouseEvent *e) {};
	handler.MouseCrossed = [] (uiAreaHandler *ha, uiArea *a, int left) {};
	handler.DragBroken = [] (uiAreaHandler *ah, uiArea *a) {};
	handler.KeyEvent = [] (uiAreaHandler *ah, uiArea *a, uiAreaKeyEvent *e) {return 0;};

	histogram = uiNewArea(&handler);
	uiBoxAppend(mainLayout, uiControl(histogram), 1);
}

void Histogramm::setupToolbox()
{

	// for a random number you need a seeder, an engine and a distribution
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(0, 100);

	for (int i = 0; i < 10; i++) {
		datapoints[i] = uiNewSpinbox(0, 100);
		uiSpinboxSetValue(datapoints[i], dist(engine));
		// uiSpinboxOnChanged(datapoints[i], onDatapointChanged, NULL);
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
	uiColorButtonOnChanged(colorButton, [] (uiColorButton *b, void *data) {} , NULL);
	uiBoxAppend(toolbox, uiControl(colorButton), 0);
}

void Histogramm::show()
{
    uiControlShow(uiControl(mainwin));
}

void Histogramm::exec()
{
    uiMain();
}


int main()
{
    Histogramm histogramm{};
    histogramm.setupWindow("libui Histogram Example");
    histogramm.setupToolbox();
    histogramm.show();
    histogramm.exec();
}
