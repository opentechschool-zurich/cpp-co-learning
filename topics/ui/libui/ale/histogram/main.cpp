// andreas.gieriet@externsoft.ch
#include "histogram.h"
#include "window.h"

using namespace std;

int main()
{
    Histogram histogram;

    Window mainWindow("Histogram");
    mainWindow.show();

    return histogram.exec();
}