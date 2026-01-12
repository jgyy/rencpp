#include "gameengine.h"
#include "mainwindow.h"
#include <QApplication>
#include <QProcessEnvironment>

int main(int argc, char *argv[]) {
  qputenv("QT_QPA_PLATFORM", "xcb");

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

  QApplication app(argc, argv);

  GameEngine gameEngine;

  MainWindow window(&gameEngine);
  window.show();

  return app.exec();
}
