#include <wx-3.0/wx/gdicmn.h>

#include "BasicDrawPane.h"
#include "Definitions.h"
#include "Circle.h"

BasicDrawPane::BasicDrawPane(wxFrame* parent) :
wxPanel(parent), m_timer(this, TIMER_ID), m_create_timer(this, CREATE_TIMER_ID)
{
     m_timer.Start(20);    // interval in ms
     m_create_timer.Start(1000);    // interval in ms
}


void BasicDrawPane::mouseClicked(wxMouseEvent& event) {
    wxPoint mousePoint = event.GetLogicalPosition(wxClientDC(this));
    vectorMtx.lock();
    vectorOfCirclePointers.push_back(new Circle{mousePoint.x, mousePoint.y , 25, (rand() % 250) + 100, static_cast< float >(rand() % 360), 2.0});
    vectorMtx.unlock();
    Refresh();
}

/**
 * Creates a number of new Circles that move radially away from the supplied x and y coordinates
 * @param newFragments The vector to add the new fragments to
 * @param fragments The number of fragments to create
 * @param x the coordinates of the new fragments to burst away from
 * @param y the coordinates of the new fragments to burst away from
 */
void explode( std::vector<Circle*> & newFragments, int fragments, int x, int y, int speed = 200, float timeToLive = 1.0 ) {
    for ( int i = 0; i < fragments; ++i) {
        float angle = i * 360 / fragments;
        Circle* fragment = new Circle {x, y, 5, speed, static_cast<float>(angle), timeToLive };
        fragment->setColor(wxColor(255,0,0));
        fragment->setCircleType(Dies);
        newFragments.push_back(fragment);
    }
}


/**
 * This method is called by the wxTimer. We use this event to update the position
 * of all our objects.
 * 
 * @param event The timer event
 */
void BasicDrawPane::OnTimer(wxTimerEvent& event)
{
    // figure out how much time passed since the last time we were called
    // Should correspond to the event timer.
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    double deltaTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTimePoint).count();
    double deltaTimeS = deltaTimeMs / 1000.0;
    lastUpdateTimePoint = now;

    // create a new vector to add the fragments if any so as to avoid a concurrent modification
    std::vector<Circle*> newFragments;
    vectorMtx.lock();
    for (auto cptr : vectorOfCirclePointers ) {
        //cptr->move(deltaTimeS);
        if ( cptr->isExpired() && cptr->explodesAtEnd() ) {
            wxPoint position = cptr->position.getPosition( cptr->getAge() );
            explode(newFragments, 25, position.x, position.y);
        }
    }
    // merge the vectors
    vectorOfCirclePointers.insert(vectorOfCirclePointers.end(), newFragments.begin(), newFragments.end());
    
    wxSize panelSize=GetClientSize();
    // remove circles that have expired and delete them from the heap using a lambda
    vectorOfCirclePointers.erase(
        std::remove_if(
            vectorOfCirclePointers.begin(),
            vectorOfCirclePointers.end(),
            [panelSize](Circle *c) -> bool {
                wxPoint position = c->position.getPosition( c->getAge() );
                if ( position.x < 0 || position.x > panelSize.GetWidth() || position.y < 0 || position.y > panelSize.GetHeight() || c->isExpired() ) {
                    delete c;
                    return true;
                } else {
                    return false;
                }
            }
        ),
        vectorOfCirclePointers.end()
    );
    vectorMtx.unlock();
    Refresh();
}

void BasicDrawPane::OnCreateTimer(wxTimerEvent& event) {
    vectorMtx.lock();
    wxSize panelSize=GetClientSize();
    int horizontalItems = 3;
    int verticalItems = 3;
    int hw = panelSize.GetWidth() / (horizontalItems + 1);
    int vh = panelSize.GetHeight() / (verticalItems + 1);
    for (int i = 1; i <= horizontalItems; ++i ) {
        for (int j = 1; j <= verticalItems; ++j ) {
            vectorOfCirclePointers.push_back(new Circle{ i * hw, j * vh , 15, 150, 30.0, 0.4});
        }
    }
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
void BasicDrawPane::render(wxDC&  dc)
{
    dc.Clear();
    // draw some text
    //dc.DrawText(wxT("Testing"), 40, 60);

    vectorMtx.lock();
    for ( Circle* c : vectorOfCirclePointers ) {
        dc.SetBrush(c->getColor()); // filling
        dc.SetPen(  wxPen( c->getColor(), 1 ) );  // color & pend width
        c->render( dc );
        //dc.DrawCircle( wxPoint(c->x,c->y), c->radius );
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
