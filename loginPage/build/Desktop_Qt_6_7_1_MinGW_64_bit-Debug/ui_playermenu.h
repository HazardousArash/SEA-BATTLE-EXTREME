/********************************************************************************
** Form generated from reading UI file 'playermenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERMENU_H
#define UI_PLAYERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playerMenu
{
public:
    QWidget *centralwidget;
    QPushButton *vsbbotPB;
    QPushButton *CoPB;
    QPushButton *onlinePB;
    QPushButton *statsPB;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *playerMenu)
    {
        if (playerMenu->objectName().isEmpty())
            playerMenu->setObjectName("playerMenu");
        playerMenu->resize(800, 600);
        playerMenu->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        centralwidget = new QWidget(playerMenu);
        centralwidget->setObjectName("centralwidget");
        vsbbotPB = new QPushButton(centralwidget);
        vsbbotPB->setObjectName("vsbbotPB");
        vsbbotPB->setGeometry(QRect(280, 80, 211, 51));
        vsbbotPB->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
"\n"
""));
        CoPB = new QPushButton(centralwidget);
        CoPB->setObjectName("CoPB");
        CoPB->setGeometry(QRect(280, 160, 211, 51));
        CoPB->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        onlinePB = new QPushButton(centralwidget);
        onlinePB->setObjectName("onlinePB");
        onlinePB->setGeometry(QRect(280, 240, 211, 51));
        onlinePB->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        statsPB = new QPushButton(centralwidget);
        statsPB->setObjectName("statsPB");
        statsPB->setGeometry(QRect(280, 350, 211, 51));
        statsPB->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 460, 191, 51));
        playerMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(playerMenu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 45));
        playerMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(playerMenu);
        statusbar->setObjectName("statusbar");
        playerMenu->setStatusBar(statusbar);

        retranslateUi(playerMenu);

        QMetaObject::connectSlotsByName(playerMenu);
    } // setupUi

    void retranslateUi(QMainWindow *playerMenu)
    {
        playerMenu->setWindowTitle(QCoreApplication::translate("playerMenu", "MainWindow", nullptr));
        vsbbotPB->setText(QCoreApplication::translate("playerMenu", "VS BOT", nullptr));
        CoPB->setText(QCoreApplication::translate("playerMenu", "CO-OP", nullptr));
        onlinePB->setText(QCoreApplication::translate("playerMenu", "Online", nullptr));
        statsPB->setText(QCoreApplication::translate("playerMenu", "Stats", nullptr));
        pushButton->setText(QCoreApplication::translate("playerMenu", "Main Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class playerMenu: public Ui_playerMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERMENU_H
