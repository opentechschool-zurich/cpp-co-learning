#pragma once

#include <math.h>
#include <chrono>
#include <wx/colour.h>

enum CircleType {Explodes, Dies};

class Circle {
    
private:
    float deltaX = 0; // delta for X in pixels per second
    float deltaY = 0; // delta for y in pixels per second
    static constexpr float  PI_F=3.14159265358979f;
    std::chrono::steady_clock::time_point created = std::chrono::steady_clock::now();
    wxColor color = wxColor(0,0,255);
    wxColor endColor = wxColor(0,100,100);
    CircleType circleType = Explodes;
    
public:
    float x;
    float y;
    int radius; // in pixels
    int speed; // pixels per second
    float angle; // in degrees
    int timeToLive; // in ms
    Circle(int x = 0, int y = 0, int radius = 0, int speed = 250, float angle = 0.0, int timeToLive = 2000 ) 
            : x(x), y(y), radius(radius), speed(speed), angle(angle), timeToLive(timeToLive) {
        float radiansAngle = angle * PI_F / 180;
        deltaX = speed * cos(radiansAngle);
        deltaY = speed * sin(radiansAngle);
    }
    
    /**
     * Moves the x and y by the pre-calculated deltaX and deltaY.
     * The idea being to avoid the costly floating point trigonometry call.
     * @param deltaTime in seconds
     */
    void move (float deltaTime) {
        x += deltaX * deltaTime;
        y += deltaY * deltaTime;
    }
    
    
    /**
     * Returns if the time to live has expired by calculating the difference
     * between the current timestamp and the timestamp of the creation.
     * @return true if expired, false if not.
     */
    bool isExpired() {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double deltaTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - created).count();
        return deltaTimeMs > timeToLive;
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
   
};
