#include "mainWindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Mondrian");
}

void MainWindow::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);

    painter.drawEllipse(QPoint(100, 100), 20, 20);
    painter.drawEllipse(QPoint(120, 100), 40, 40);
    painter.drawEllipse(QPoint(140, 100), 60, 60);
}
