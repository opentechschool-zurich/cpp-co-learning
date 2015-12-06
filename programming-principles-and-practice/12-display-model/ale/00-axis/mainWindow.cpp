#include "mainWindow.h"
#include <QPainter>
#include <QPoint>

#include "axis.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Canvas");
}

void MainWindow::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);
    Axis axis(painter);
    axis.draw(Axis::x, QPoint(50,200), 90, 10, "X Axis");
    axis.draw(Axis::y, QPoint(50,200), 90, 10, "Y Axis");
}
