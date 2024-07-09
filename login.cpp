#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "login.h"
void runLogin(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
}
