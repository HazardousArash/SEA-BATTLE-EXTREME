#include "gameWindow.h"
#include "globalVariables.h"
#include <QApplication>

void runGame() {
    //QApplication a(argc, argv);
    GameWindow* w=new GameWindow();
    w->show();
}
