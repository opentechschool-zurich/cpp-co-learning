#include "mainWindow.h"
#include <QPainter>
#include <QImage>
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Image");
}

void MainWindow::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);

    QPoint point(10, 20);

    QImage image = QImage("robot.jpg");

    painter.drawImage(point, image);
}
