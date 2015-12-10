#include "mainWindow.h"
#include <QPainter>
#include <vector>
#include <string>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Color Table");
}

void MainWindow::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);

    std::vector<std::string> colors = {"#000000", "#800000", "#008000", "#808000", "#000080", "#800080", "#008080", "#c0c0c0", "#808080", "#ff0000", "#00ff00", "#ffff00", "#0000ff", "#ff00ff", "#00ffff", "#ffffff", "#000000", "#00005f", "#000087", "#0000af", "#0000d7", "#0000ff", "#005f00", "#005f5f", "#005f87", "#005faf", "#005fd7", "#005fff", "#008700", "#00875f", "#008787", "#0087af", "#0087d7", "#0087ff", "#00af00", "#00af5f", "#00af87", "#00afaf", "#00afd7", "#00afff", "#00d700", "#00d75f", "#00d787", "#00d7af", "#00d7d7", "#00d7ff", "#00ff00", "#00ff5f", "#00ff87", "#00ffaf", "#00ffd7", "#00ffff", "#5fff00", "#5fff5f", "#5fff87", "#5fffaf", "#5fffd7", "#5fffff", "#5fd700", "#5fd75f", "#5fd787", "#5fd7af", "#5fd7d7", "#5fd7ff", "#5faf00", "#5faf5f", "#5faf87", "#5fafaf", "#5fafd7", "#5fafff", "#5f8700", "#5f875f", "#5f8787", "#5f87af", "#5f87d7", "#5f87ff", "#5f5f00", "#5f5f5f", "#5f5f87", "#5f5faf", "#5f5fd7", "#5f5fff", "#5f0000", "#5f005f", "#5f0087", "#5f00af", "#5f00d7", "#5f00ff", "#8700ff", "#8700d7", "#8700af", "#870087", "#87005f", "#870000", "#875fff", "#875fd7", "#875faf", "#875f87", "#875f5f", "#875f00", "#8787ff", "#8787d7", "#8787af", "#878787", "#87875f", "#878700", "#87afff", "#87afd7", "#87afaf", "#87af87", "#87af5f", "#87af00", "#87d7ff", "#87d7d7", "#87d7af", "#87d787", "#87d75f", "#87d700", "#87ffff", "#87ffd7", "#87ffaf", "#87ff87", "#87ff5f", "#87ff00", "#afffff", "#afffd7", "#afffaf", "#afff87", "#afff5f", "#afff00", "#afd7ff", "#afd7d7", "#afd7af", "#afd787", "#afd75f", "#afd700", "#afafff", "#afafd7", "#afafaf", "#afaf87", "#afaf5f", "#afaf00", "#af87ff", "#af87d7", "#af87af", "#af8787", "#af875f", "#af8700", "#af5fff", "#af5fd7", "#af5faf", "#af5f87", "#af5f5f", "#af5f00", "#af00ff", "#af00d7", "#af00af", "#af0087", "#af005f", "#af0000", "#d70000", "#d7005f", "#d70087", "#d700af", "#d700d7", "#d700ff", "#d75f00", "#d75f5f", "#d75f87", "#d75faf", "#d75fd7", "#d75fff", "#d78700", "#d7875f", "#d78787", "#d787af", "#d787d7", "#d787ff", "#dfaf00", "#dfaf5f", "#dfaf87", "#dfafaf", "#dfafdf", "#dfafff", "#dfdf00", "#dfdf5f", "#dfdf87", "#dfdfaf", "#dfdfdf", "#dfdfff", "#dfff00", "#dfff5f", "#dfff87", "#dfffaf", "#dfffdf", "#dfffff", "#ffff00", "#ffff5f", "#ffff87", "#ffffaf", "#ffffdf", "#ffffff", "#ffdf00", "#ffdf5f", "#ffdf87", "#ffdfaf", "#ffdfdf", "#ffdfff", "#ffaf00", "#ffaf5f", "#ffaf87", "#ffafaf", "#ffafdf", "#ffafff", "#ff8700", "#ff875f", "#ff8787", "#ff87af", "#ff87df", "#ff87ff", "#ff5f00", "#ff5f5f", "#ff5f87", "#ff5faf", "#ff5fdf", "#ff5fff", "#ff0000", "#ff005f", "#ff0087", "#ff00af", "#ff00df", "#ff00ff", "#080808", "#121212", "#1c1c1c", "#262626", "#303030", "#3a3a3a", "#444444", "#4e4e4e", "#585858", "#626262", "#6c6c6c", "#767676", "#eeeeee", "#e4e4e4", "#dadada", "#d0d0d0", "#c6c6c6", "#bcbcbc", "#b2b2b2", "#a8a8a8", "#9e9e9e", "#949494", "#8a8a8a", "#808080"};

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            auto rgb = colors[i * 16 + j];
            std::vector<int> color{};
            for (int k = 1; k < 7; k += 2) {
                int myint = std::stoi(rgb.substr(k, 2), nullptr, 16);
                color.push_back(myint);
            }
            QRect rectangle = QRect(QPoint(i * 20, j * 20), QSize(20, 20));
            painter.fillRect(rectangle, QColor(color[0], color[1], color[2]));
            painter.drawRect(rectangle);
        }
    }
}
