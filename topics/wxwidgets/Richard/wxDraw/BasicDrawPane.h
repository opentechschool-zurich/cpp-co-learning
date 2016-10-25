#pragma once

#include "wx/wx.h"
#include <vector>
#include "Renderable.h"
#include <chrono>
#include <mutex>

class BasicDrawPane : public wxPanel {
public:
    BasicDrawPane(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);
    void mouseClicked(wxMouseEvent& event);
    
    /**
     * The update timer fires reasonably often and asks the Renderables to 
     * update their position.
     * @param event The timer event
     */
    void OnUpdateTimer(wxTimerEvent& event);
    
    /**
     * The create timer fires every few seconds and starts new Fireworks
     * @param event
     */
    void OnCreateTimer(wxTimerEvent& event);

    std::vector<Renderable*> vectorOfRenderablePointers;
    std::mutex vectorMtx; // mutex to prevent concurrent modifications on vector
    
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
    wxTimer updateTimer;
    wxTimer createTimer;
    std::chrono::steady_clock::time_point lastUpdateTimePoint = std::chrono::steady_clock::now();
};

