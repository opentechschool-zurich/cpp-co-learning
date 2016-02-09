// Chapter 12
// Buch 12.7: using shape primitives p. 874, 
// p 892: [12.8]
//- Shape is defined in Graph.h as a struct
//- Graph.h is a Point.h
//- main has a Graph.h

// Chapter 13: Graphic classes

#ifndef ARC_H
#define ARC_H

#include "Graph.h"
using namespace Graph_lib;

class Arc::Shape{

    public:
    Arc();    
    void add(Point, Point);
};

# endif
