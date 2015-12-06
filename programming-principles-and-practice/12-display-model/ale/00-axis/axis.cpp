#include "axis.h"
#include<QPainter>
#include <QPoint>
#include <QString>

/**
 * draw an axis of of length for the x or y axis, with ticks at each step
 */
void Axis::draw(char axis, QPoint start, int length, int step, QString label)
{
    QVector<QLine> lines;
    QPoint tickStart{start};
    QPoint tickEnd{0, 0};
    QPoint tickStep{0,0};
    QPoint labelPos{0,0};
    int n{length / step};
    if (axis == Axis::x) {
        tickStep = QPoint(step, 0);
        tickEnd = QPoint(start.x(), start.y() - 5);
        lines << QLine(start, QPoint(start.x() + length, start.y()));
        labelPos = QPoint(start.x(), start.y() + 15);
    } else if (axis == Axis::y) {
        tickStep = QPoint(0, -step);
        tickEnd = QPoint(start.x() + 5, start.y());
        lines << QLine(start, QPoint(start.x(), start.y() - length));
        labelPos = QPoint(start.x(), start.y() - length - 5);
    }
    for (int i = 0; i < n; i++) {
        tickStart += tickStep;
        tickEnd += tickStep;
        lines << QLine(tickStart, tickEnd);
    }
    painter.drawLines(lines);
    painter.drawText(labelPos, label);
}
