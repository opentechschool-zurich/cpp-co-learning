#pragma once
#include <wx/dc.h>
#include <wx/gdicmn.h>
#include <vector>

class Renderable {
public:

    /**
     * Draws the circle 
     * @param dc
     */
    virtual auto render(wxDC& dc) -> void = 0;

    /**
     * Returns if the Renderable 
     * @return true if expired, false if not.
     */
    virtual auto isExpired() -> bool = 0;

    /**
     * The action to perform at the end of the lifecycle. The method is
     * passed a vector to which it is free to add new renderables. These 
     * will later be merged into the master table.
     * @param renderables A vector to add the new renderables to
     */
    virtual auto endAction(std::vector<Renderable*> &renderables) -> void = 0;
    
    /**
     * Returns the position of the Renderable
     * @return the position of the Renderable
     */
    virtual auto getPosition() -> wxPoint = 0;
    
};