#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "application.h"
/**
 * @brief Bootstrap the Histogram application
 */
class Histogram: public Application
{
    public:
        Histogram(): Application() {}
        int exec();
};

#endif
