#include "mainWindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Grid");
}

void MainWindow::paintEvent(QPaintEvent* /* event */)
{
    auto windowWidth = this->width();
    auto windowHeight = this->height();
    auto gridWidth = 80;
    auto gridHeight = 40;

    QVector<QLine> lines;
    for (auto x = gridWidth; x < windowWidth; x += gridWidth) {
        lines << QLine(QPoint(x, 0), QPoint(x, windowHeight));
    }
    for (auto y = gridHeight; y < windowHeight; y += gridHeight) {
        lines << QLine(QPoint(0, y), QPoint(windowWidth, y));
    }

    QPainter painter(this);
    painter.drawLines(lines);
}
