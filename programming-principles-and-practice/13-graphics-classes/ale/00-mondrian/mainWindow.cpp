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

    QRect rectangle;
    rectangle = QRect(QPoint(150, 100), QSize(200, 100));
    painter.drawRect(rectangle);
    painter.fillRect(rectangle, Qt::yellow);
    rectangle = QRect(QPoint(50, 50), QSize(200, 100));
    painter.fillRect(rectangle, Qt::blue);
    painter.drawRect(rectangle);
    rectangle = QRect(QPoint(50, 150), QSize(200, 100));
    painter.fillRect(rectangle, Qt::red);
    painter.drawRect(rectangle);
    rectangle = QRect(QPoint(250, 50), QSize(200, 100));
    painter.fillRect(rectangle, Qt::green);
    painter.drawRect(rectangle);
    painter.drawRect(QRect(QPoint(250, 150), QSize(200, 100)));
}
