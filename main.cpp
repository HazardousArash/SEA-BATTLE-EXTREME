#include "gameWindow.h"
#include "globalVariables.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();

}
