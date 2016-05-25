//#include <cstddef>
#include "saw.h"

Saw::Saw() 
{
    blade_width = 4;
    clamping_width = 40;
}

int Saw::cut(Dowel &stockpiece, Dowel *workpiece, const int length) {

    int error = 0;

    workpiece = nullptr;

    if (length<=0) {
        error = 429;
        invalidlength e;
        throw(e);
    }

    // TODO: Implement the cutting procedure

    stockpiece.setlength(stockpiece.getlength() - blade_width - length);

    if (error == 0) {
        workpiece = new Dowel(length);
    }
    return error;

}
