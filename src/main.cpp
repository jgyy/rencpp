#include <QApplication>
#include <QProcessEnvironment>
#include "gameengine.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "xcb");

    QApplication app(argc, argv);

    GameEngine gameEngine;

    MainWindow window(&gameEngine);
    window.show();

    return app.exec();
}
