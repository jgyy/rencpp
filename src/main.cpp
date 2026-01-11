#include <QApplication>
#include "gameengine.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameEngine gameEngine;

    MainWindow window(&gameEngine);
    window.show();

    return app.exec();
}
