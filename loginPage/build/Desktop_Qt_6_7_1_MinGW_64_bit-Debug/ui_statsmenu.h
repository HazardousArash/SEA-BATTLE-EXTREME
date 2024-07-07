/********************************************************************************
** Form generated from reading UI file 'statsmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSMENU_H
#define UI_STATSMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_statsMenu
{
public:
    QWidget *centralwidget;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *statsMenu)
    {
        if (statsMenu->objectName().isEmpty())
            statsMenu->setObjectName("statsMenu");
        statsMenu->resize(800, 600);
        statsMenu->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
"\n"
""));
        centralwidget = new QWidget(statsMenu);
        centralwidget->setObjectName("centralwidget");
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(130, 100, 531, 251));
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(50, 400, 231, 71));
        pushButton->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);color:rgb(0, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        statsMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(statsMenu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 45));
        statsMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(statsMenu);
        statusbar->setObjectName("statusbar");
        statsMenu->setStatusBar(statusbar);

        retranslateUi(statsMenu);

        QMetaObject::connectSlotsByName(statsMenu);
    } // setupUi

    void retranslateUi(QMainWindow *statsMenu)
    {
        statsMenu->setWindowTitle(QCoreApplication::translate("statsMenu", "MainWindow", nullptr));
        plainTextEdit->setPlainText(QString());
        pushButton->setText(QCoreApplication::translate("statsMenu", "Previous Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class statsMenu: public Ui_statsMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSMENU_H
