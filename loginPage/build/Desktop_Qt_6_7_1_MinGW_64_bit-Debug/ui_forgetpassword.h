/********************************************************************************
** Form generated from reading UI file 'forgetpassword.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGETPASSWORD_H
#define UI_FORGETPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_forgetPassword
{
public:
    QWidget *centralwidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *userLine;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *SkeyLine;
    QLabel *label_4;
    QLineEdit *NPassLine;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *forgetPassword)
    {
        if (forgetPassword->objectName().isEmpty())
            forgetPassword->setObjectName("forgetPassword");
        forgetPassword->resize(800, 600);
        forgetPassword->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 0);color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";\n"
""));
        centralwidget = new QWidget(forgetPassword);
        centralwidget->setObjectName("centralwidget");
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(240, 150, 331, 178));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        userLine = new QLineEdit(formLayoutWidget);
        userLine->setObjectName("userLine");

        formLayout->setWidget(0, QFormLayout::FieldRole, userLine);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_2);

        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        SkeyLine = new QLineEdit(formLayoutWidget);
        SkeyLine->setObjectName("SkeyLine");

        formLayout->setWidget(1, QFormLayout::FieldRole, SkeyLine);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        NPassLine = new QLineEdit(formLayoutWidget);
        NPassLine->setObjectName("NPassLine");

        formLayout->setWidget(3, QFormLayout::FieldRole, NPassLine);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(310, 300, 181, 61));
        pushButton->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 0);color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";\n"
""));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(80, 430, 171, 29));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 0);color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";\n"
""));
        forgetPassword->setCentralWidget(centralwidget);
        menubar = new QMenuBar(forgetPassword);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 36));
        forgetPassword->setMenuBar(menubar);
        statusbar = new QStatusBar(forgetPassword);
        statusbar->setObjectName("statusbar");
        forgetPassword->setStatusBar(statusbar);

        retranslateUi(forgetPassword);

        QMetaObject::connectSlotsByName(forgetPassword);
    } // setupUi

    void retranslateUi(QMainWindow *forgetPassword)
    {
        forgetPassword->setWindowTitle(QCoreApplication::translate("forgetPassword", "MainWindow", nullptr));
        label_2->setText(QString());
        label->setText(QCoreApplication::translate("forgetPassword", "UserName", nullptr));
        label_3->setText(QCoreApplication::translate("forgetPassword", "Security Key", nullptr));
        label_4->setText(QCoreApplication::translate("forgetPassword", "new Password", nullptr));
        pushButton->setText(QCoreApplication::translate("forgetPassword", "Change Password", nullptr));
        pushButton_2->setText(QCoreApplication::translate("forgetPassword", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class forgetPassword: public Ui_forgetPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGETPASSWORD_H
