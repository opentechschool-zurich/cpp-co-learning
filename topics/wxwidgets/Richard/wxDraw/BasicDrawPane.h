#pragma once

#include "wx/wx.h"
#include <vector>
#include "Circle.h"
#include <chrono>
#include <mutex>

class BasicDrawPane : public wxPanel {

public:
    BasicDrawPane(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);
    void mouseClicked(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()

private:
        std::vector<Circle*> vectorOfCirclePointers;
        std::mutex vectorMtx; // mutex to prevent concurrent modifications on vector
        wxTimer m_timer;
        std::chrono::steady_clock::time_point lastUpdateTimePoint = std::chrono::steady_clock::now();
};

