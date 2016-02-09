// Chapter 12
// Buch 12.7: using shape primitives p. 874, 
// p 892: [12.8]
//- Shape is defined in Graph.h as a struct
//- Graph.h is a Point.h
//- main has a Graph.h

// Chapter 13: Graphic classes

#include "Graph.h"
#include "Arc.h"

// empty: can be declard directly in class
Arc::Arc() {
}

void Arc::add(Point p1, Point p2, Point p3, Point p4){
    Shape::add(p1);
    Shape::add(p2);
    Shape::add(p3);
    Shape::add(p4);
}