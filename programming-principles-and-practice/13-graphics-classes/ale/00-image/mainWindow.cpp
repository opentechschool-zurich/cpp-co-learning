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


    QRect target = painter.viewport();
    QRect source = QRect(QPoint(10,20), QSize(200, 200));

    QImage image = QImage("robot.jpg");

    painter.drawImage(target, image, source);

    // QPoint point(0, 0);
    // QImage imageSmall = QImage("robot.jpg");
    // painter.drawImage(point, imageSmall);
}
