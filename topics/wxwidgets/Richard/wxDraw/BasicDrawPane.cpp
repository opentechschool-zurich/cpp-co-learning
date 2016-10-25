#include "Definitions.h"
#include "BasicDrawPane.h"
#include "Circle.h"

BasicDrawPane::BasicDrawPane(wxFrame *parent) :
wxPanel(parent), updateTimer(this, TIMER_ID), createTimer(this, CREATE_TIMER_ID) {
    updateTimer.Start(20); // interval in ms
    createTimer.Start(1000); // interval in ms
}

void BasicDrawPane::mouseClicked(wxMouseEvent& event) {
    wxPoint mousePoint = event.GetLogicalPosition(wxClientDC(this));
    vectorMtx.lock();
    Circle *c_pt = new Circle{mousePoint.x, mousePoint.y, 25, (rand() % 250) + 100, static_cast<float> (rand() % 360), 2.0};
    vectorOfRenderablePointers.push_back(c_pt);
    vectorMtx.unlock();
    Refresh();
}


void BasicDrawPane::OnCreateTimer(wxTimerEvent& event) {
    vectorMtx.lock();
    wxSize panelSize = GetClientSize();
    int horizontalItems = 3;
    int verticalItems = 3;
    int hw = panelSize.GetWidth() / (horizontalItems + 1);
    int vh = panelSize.GetHeight() / (verticalItems + 1);
    for (int i = 1; i <= horizontalItems; ++i) {
        for (int j = 1; j <= verticalItems; ++j) {
            vectorOfRenderablePointers.push_back(new Circle{i * hw, j * vh, 15, 150, 30.0, 0.4});
        }
    }
    vectorMtx.unlock();
    Refresh();
}

void BasicDrawPane::OnUpdateTimer(wxTimerEvent& event) {
    // figure out how much time passed since the last time we were called
    // Should correspond to the event timer.
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    double deltaTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTimePoint).count();
    double deltaTimeS = deltaTimeMs / 1000.0;
    lastUpdateTimePoint = now;

    // allow the Renderables to perform an endAction if required
    vectorMtx.lock();
    std::vector<Renderable*> newRenderables;
    for (auto r : vectorOfRenderablePointers) {
        r->endAction(newRenderables);
    }
    // merge the vectors
    vectorOfRenderablePointers.insert(vectorOfRenderablePointers.end(), newRenderables.begin(), newRenderables.end());


    // remove Renderables that have expired or moved off the screen
    wxSize panelSize = GetClientSize();
    vectorOfRenderablePointers.erase(
            std::remove_if(
            vectorOfRenderablePointers.begin(),
            vectorOfRenderablePointers.end(),
            [panelSize](Renderable * r) -> bool {
                wxPoint position = r->getPosition();
                if (position.x < 0 || position.x > panelSize.GetWidth() || position.y < 0 || position.y > panelSize.GetHeight() || r->isExpired()) {
                    delete r;
                    return true;
                } else {
                    return false;
                }
            }
    ),
    vectorOfRenderablePointers.end()
            );
    vectorMtx.unlock();
    Refresh();
}



// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 */

/**
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
void BasicDrawPane::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}

/**
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC& dc) {
    dc.Clear();

    vectorMtx.lock();
    for (Renderable *r : vectorOfRenderablePointers) {
        r->render(dc);
    }
    vectorMtx.unlock();

    // draw a rectangle
    //dc.SetBrush(*wxBLUE_BRUSH); // blue filling
    //dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
    //dc.DrawRectangle( 300, 100, 400, 200 );

    // draw a line
    //dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    //dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle

    // Look at the wxDC docs to learn how to draw other stuff
}
