#include "application.h"

#include "libui/ui.h"
#include <system_error>

using namespace std;

Application::Application()
{
    uiInitOptions o = {};

    if (uiInit(&o) != NULL) {
        throw  system_error();
    }
}
