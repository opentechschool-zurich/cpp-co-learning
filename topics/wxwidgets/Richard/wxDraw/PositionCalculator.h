#pragma once

#include <wx/gdicmn.h>

class PositionCalculator {
public:
    virtual wxPoint getPosition( double seconds) = 0;
};
