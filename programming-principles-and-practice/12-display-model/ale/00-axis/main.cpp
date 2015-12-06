#include <QApplication>
#include <mainWindow.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(800, 600);
    window.show();
    return app.exec();
}
