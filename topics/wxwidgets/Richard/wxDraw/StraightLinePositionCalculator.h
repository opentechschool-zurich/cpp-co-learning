#pragma once

#include "PositionCalculator.h"
#include <math.h>

class StraightLinePositionCalculator : public PositionCalculator {
public:
    StraightLinePositionCalculator()
    : startingPosition(wxPoint {150,150}) {}
    
    StraightLinePositionCalculator(wxPoint & startingPosition, int speed = 250, float angle = 0.0)
    : startingPosition(startingPosition), speed(speed), angle(angle) {
        float radiansAngle = angle * PI_F / 180;
        deltaX = speed * cos(radiansAngle);
        deltaY = speed * sin(radiansAngle);
    }
    
    wxPoint getPosition(const double seconds) override {
        return wxPoint( startingPosition.x + seconds * deltaX, startingPosition.y + seconds * deltaY );
    }

private:
    static constexpr float  PI_F=3.14159265358979f;
    wxPoint startingPosition;
    float deltaX = 0; // delta for X in pixels per second
    float deltaY = 0; // delta for y in pixels per second
    int speed; // pixels per second
    float angle; // in degrees


};