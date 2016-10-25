#pragma once

#include <math.h>
#include <chrono>
#include <wx/colour.h>
#include "StraightLinePositionCalculator.h"
#include <wx/dc.h>
#include <iostream>
#include "Renderable.h"
#include <wx/gdicmn.h>
#include <mutex>

enum CircleType {
    Explodes, Dies
};

class Circle : public Renderable {
private:
    static constexpr float PI_F = 3.14159265358979f;
    std::chrono::steady_clock::time_point created = std::chrono::steady_clock::now();
    wxColor color = wxColor(0, 0, 255);
    wxColor endColor = wxColor(0, 100, 100);
    CircleType circleType = Explodes;

public:
    StraightLinePositionCalculator position;
    int radius; // in pixels
    float timeToLive; // in s

    Circle(int x = 0, int y = 0, int radius = 0, int speed = 250, float angle = 0.0, float timeToLive = 2.0)
    : radius(radius), timeToLive(timeToLive) {
        wxPoint p = wxPoint(x, y);
        position = StraightLinePositionCalculator(p, speed, angle);
    }


    /**
     * How long the circle has existed since it was created
     * @return the time in seconds
     */
    auto getAge() -> double;

    /**
     * Returns if the circle is expired based on the age being greater than 
     * the defined timeToLive
     * @return true if expired, false if not.
     */
    auto isExpired() -> bool;

    /**
     * Returns the color of the circle
     * @return the color of the circle
     */
    auto getColor() {
        return color;
    }

    /**
     * Sets the color for the circle
     */
    auto setColor(wxColor newColor) {
        color = newColor;
    }

    /**
     * Returns true if the circle explodes at the end of its life
     * @return 
     */
    auto explodesAtEnd() -> bool {
        return circleType == Explodes;
    }

    /**
     * Creates a number of new Circles that move radially away from the supplied x and y coordinates
     * @param newFragments The vector to add the new fragments to
     * @param fragments The number of fragments to create
     * @param x the coordinates of the new fragments to burst away from
     * @param y the coordinates of the new fragments to burst away from
     */
    auto explode(std::vector<Renderable*> &newFragments, int fragments, int x, int y, int speed = 200, float timeToLive = 1.0) -> void {
        for (int i = 0; i < fragments; ++i) {
            float angle = i * 360 / fragments;
            Circle* fragment = new Circle{x, y, 5, speed, static_cast<float> (angle), timeToLive};
            fragment->setColor(wxColor(255, 0, 0));
            fragment->setCircleType(Dies);
            newFragments.push_back(fragment);
        }
    }

    auto endAction(std::vector<Renderable*> &renderables) -> void {
        if (isExpired() && explodesAtEnd()) {
            wxPoint position = getPosition();
            explode(renderables, 25, position.x, position.y);
        }
    }

    /**
     * Setter for the circleType
     * @param type
     */
    auto setCircleType(CircleType type) -> void {
        circleType = type;
    }

    /**
     * Draws the circle 
     * @param dc
     */
    auto render(wxDC& dc) -> void {
        dc.SetBrush(getColor()); // filling
        dc.SetPen(wxPen(getColor(), 1)); // color & pend width
        dc.DrawCircle(getPosition(), radius);
    }

    /**
     * Returns the position of the circle
     * @return The position of the circle
     */
    auto getPosition() -> wxPoint {
        return position.getPosition(getAge());
    }
};
