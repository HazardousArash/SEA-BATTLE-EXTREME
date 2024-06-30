/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QLabel *gridBackgroundLabel;
    QLabel *tableLabel;
    QPushButton *backButton;
    QPushButton *nextButton;
    QLabel *largeShip;
    QLabel *tinyShip;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName("GameWindow");
        GameWindow->resize(1256, 779);
        gridBackgroundLabel = new QLabel(GameWindow);
        gridBackgroundLabel->setObjectName("gridBackgroundLabel");
        gridBackgroundLabel->setGeometry(QRect(80, 70, 591, 591));
        tableLabel = new QLabel(GameWindow);
        tableLabel->setObjectName("tableLabel");
        tableLabel->setGeometry(QRect(0, 0, 1271, 781));
        backButton = new QPushButton(GameWindow);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(0, 670, 141, 101));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background: transparent;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: transparent;\n"
"}\n"
""));
        backButton->setIconSize(QSize(800, 800));
        backButton->setFlat(true);
        nextButton = new QPushButton(GameWindow);
        nextButton->setObjectName("nextButton");
        nextButton->setGeometry(QRect(1130, 670, 131, 101));
        nextButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background: transparent;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: transparent;\n"
"}\n"
""));
        nextButton->setIconSize(QSize(800, 800));
        nextButton->setAutoDefault(false);
        nextButton->setFlat(true);
        largeShip = new QLabel(GameWindow);
        largeShip->setObjectName("largeShip");
        largeShip->setGeometry(QRect(820, 230, 63, 20));
        tinyShip = new QLabel(GameWindow);
        tinyShip->setObjectName("tinyShip");
        tinyShip->setGeometry(QRect(920, 240, 63, 20));
        tableLabel->raise();
        gridBackgroundLabel->raise();
        backButton->raise();
        nextButton->raise();
        largeShip->raise();
        tinyShip->raise();

        retranslateUi(GameWindow);

        nextButton->setDefault(false);


        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QCoreApplication::translate("GameWindow", "Form", nullptr));
        gridBackgroundLabel->setText(QCoreApplication::translate("GameWindow", "TextLabel", nullptr));
        tableLabel->setText(QCoreApplication::translate("GameWindow", "TextLabel", nullptr));
        backButton->setText(QString());
        nextButton->setText(QString());
        largeShip->setText(QString());
        tinyShip->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
