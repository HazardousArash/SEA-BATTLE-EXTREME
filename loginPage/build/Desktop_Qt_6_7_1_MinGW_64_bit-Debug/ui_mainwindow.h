/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *welcomeLabel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *passLine;
    QLabel *label_2;
    QLineEdit *userLine;
    QPushButton *loginButt;
    QCommandLinkButton *signupButt;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(752, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        welcomeLabel = new QLabel(centralwidget);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setGeometry(QRect(230, 50, 277, 151));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(true);
        welcomeLabel->setFont(font);
        welcomeLabel->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0);\n"
"font: italic 18pt \"Segoe UI\";\n"
""));
        welcomeLabel->setAlignment(Qt::AlignCenter);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(218, 210, 291, 131));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        passLine = new QLineEdit(gridLayoutWidget);
        passLine->setObjectName("passLine");
        passLine->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0)\n"
""));
        passLine->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passLine, 1, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0);\n"
"font: 12pt \"Segoe UI\";"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        userLine = new QLineEdit(gridLayoutWidget);
        userLine->setObjectName("userLine");
        userLine->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0)"));

        gridLayout->addWidget(userLine, 0, 2, 1, 1);

        loginButt = new QPushButton(centralwidget);
        loginButt->setObjectName("loginButt");
        loginButt->setGeometry(QRect(280, 400, 171, 41));
        loginButt->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0);\n"
"font: 16pt \"Segoe UI\";"));
        signupButt = new QCommandLinkButton(centralwidget);
        signupButt->setObjectName("signupButt");
        signupButt->setGeometry(QRect(140, 350, 221, 41));
        signupButt->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 255, 127);color:rgb(255, 0, 0);\n"
"font: 10pt \"Segoe UI\";"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 752, 45));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("MainWindow", "Welcome!", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "User Name:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "PassWord:", nullptr));
        loginButt->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        signupButt->setText(QCoreApplication::translate("MainWindow", "don't have an account?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
