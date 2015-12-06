#include "plotter.h"
#include<QPainter>
#include<QPoint>
#include <functional>

/**
 * Plot a function on the window
 */
void Plotter::draw(std::function<double(const double)> computation, int const rangeStart, int const rangeEnd, QPoint const start, int const scaleX, int const scaleY, QString const label)
{
    QPolygon points;
    for (int i = rangeStart; i < rangeEnd; i++) {
        int y = std::round(scaleY * computation(scaleX * i));
        points << start + QPoint(i, y);
    }
    painter.drawPolyline(points);
}

