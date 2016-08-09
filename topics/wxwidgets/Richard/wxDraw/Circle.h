#pragma once

#include <math.h>
#include <chrono>
#include <wx/colour.h>
#include "StraightLinePositionCalculator.h"
#include <wx/dc.h>
#include <iostream>

enum CircleType {Explodes, Dies};

class Circle {
    
private:
    static constexpr float  PI_F=3.14159265358979f;
    std::chrono::steady_clock::time_point created = std::chrono::steady_clock::now();
    wxColor color = wxColor(0,0,255);
    wxColor endColor = wxColor(0,100,100);
    CircleType circleType = Explodes;
    
public:
    StraightLinePositionCalculator position;
    int radius; // in pixels
    float timeToLive; // in s
    Circle(int x = 0, int y = 0, int radius = 0, int speed = 250, float angle = 0.0, float timeToLive = 2.0 ) 
            : radius(radius), timeToLive(timeToLive) {
        wxPoint p = wxPoint(x,y);
        position = StraightLinePositionCalculator(p, speed, angle);
    }
    
    /**
     * Moves the x and y by the pre-calculated deltaX and deltaY.
     * The idea being to avoid the costly floating point trigonometry call.
     * @param deltaTime in seconds
     *
    void move (float deltaTime) {
        x += deltaX * deltaTime;
        y += deltaY * deltaTime;
    }*/
    
    
    /**
     * How long the circle has existed since it was created
     * @return the time in seconds
     */
    double getAge() {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        int ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - created).count();
        return (double) ms / 1000;
    }
    
    /**
     * Returns if the time to live has expired by calculating the difference
     * between the current timestamp and the timestamp of the creation.
     * @return true if expired, false if not.
     */
    bool isExpired() {
        std::cout << "age: " << getAge() << " ttl: " << timeToLive << "\n";
        return getAge() > timeToLive;
    }
    
    /**
     * Returns the color of the circle
     * @return the color of the circle
     */
    wxColor getColor() { 
        return color;
        
        /*
         * Attempt to calculate a color that changes as time marches on.
         * std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double deltaTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - created).count();
        float lifePercentage = deltaTimeMs / timeToLive;
        if ( lifePercentage > 1.0 ) { lifePercentage = 1.0; }
        
        byte */
        

    }
    
    /**
     * Color Setter.
     */
    void setColor(wxColor newColor) { color = newColor; }
    
    /**
     * Returns true if the circle explodes at the end of its life
     * @return 
     */
    bool explodesAtEnd() { return circleType == Explodes; }
    
    /**
     * Setter for the circleType
     * @param type
     */
    void setCircleType( CircleType type ) { circleType = type; }

    /**
     * Draws the circle 
     * @param dc
     */
    void render( wxDC& dc) {
        //dc.DrawCircle( wxPoint(x,y), radius );    
        
        dc.DrawCircle( position.getPosition( getAge() ), radius );    
        //dc.DrawCircle( position.getPosition( 0.0 ), radius );    
    }
    
};
