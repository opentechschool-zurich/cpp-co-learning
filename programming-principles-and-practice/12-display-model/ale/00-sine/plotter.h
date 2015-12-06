#ifndef PLOTTER_H
#define PLOTTER_H

#include <QString>
#include <functional>

class QPainter;
class QPoint;

class Plotter
{

public:
    Plotter(QPainter& painter)
    : painter{painter} {};
    void draw(std::function<double(const double)> computation, const int rangeStart, const int rangeEnd, QPoint const start, int const scaleX, int const scaleY, QString const label = "");
private:
    QPainter& painter;
};

#endif
