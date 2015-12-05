#include "mainWindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Canvas");
}

void MainWindow::paintEvent(QPaintEvent* /* event */)
{
    QPolygon polygon;
    polygon << QPoint(300, 200);
    polygon << QPoint(350, 100);
    polygon << QPoint(400, 200);

    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawPolygon(polygon);
}
