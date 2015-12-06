#ifndef AXIS_H
#define AXIS_H

#include <QString>

class QPainter;
class QPoint;

class Axis
{

public:
    Axis(QPainter& painter)
    : painter{painter} {};
    void draw(char axis, QPoint start, int length, int step, QString label = "Axis");
    const static char x = 'x';
    const static char y = 'y';
private:
    QPainter& painter;
};

#endif
