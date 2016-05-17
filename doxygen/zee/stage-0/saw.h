#ifndef SAW_H
#define SAW_H

#include "dowel.h"

class Saw
{
private:
    int blade_width;
    int clamping_width;

public:
    explicit Saw();
    int get_clampinglength();
    int cut(Dowel &stockpiece, Dowel *workpiece, const int length);

};

#endif // SAW_H
