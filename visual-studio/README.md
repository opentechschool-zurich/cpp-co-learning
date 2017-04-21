# Visual Studio and c++

## Keep the console open

~~~.cpp
#include <stdlib.h>

#ifdef _WIN32
    #define WINPAUSE system("pause")
#endif
~~~

or

Right-click on your project in Visual Studio > Properties > Configuration Properties > Linker > System, change Subsystem to "Console" 

and run it without debugging (Ctrl+F5)


[Shaun on Stackoverflow](http://stackoverflow.com/a/11831066/5239250)
