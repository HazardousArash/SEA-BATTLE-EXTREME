/********************************************************************************
** Form generated from reading UI file 'singu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGU_H
#define UI_SINGU_H

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

class Ui_singU
{
public:
    QWidget *centralwidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *userLine;
    QLabel *label_2;
    QLineEdit *passLine;
    QLabel *label_3;
    QLineEdit *firstNLine;
    QLabel *label_6;
    QLineEdit *lastNLine;
    QLabel *label_4;
    QLineEdit *gmailLine;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *singU)
    {
        if (singU->objectName().isEmpty())
            singU->setObjectName("singU");
        singU->resize(800, 600);
        singU->setStyleSheet(QString::fromUtf8("background-color:rgb(146, 230, 255);color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));
        centralwidget = new QWidget(singU);
        centralwidget->setObjectName("centralwidget");
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(260, 110, 281, 231));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        userLine = new QLineEdit(formLayoutWidget);
        userLine->setObjectName("userLine");
        userLine->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));

        formLayout->setWidget(0, QFormLayout::FieldRole, userLine);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        passLine = new QLineEdit(formLayoutWidget);
        passLine->setObjectName("passLine");
        passLine->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));
        passLine->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passLine);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        firstNLine = new QLineEdit(formLayoutWidget);
        firstNLine->setObjectName("firstNLine");
        firstNLine->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));

        formLayout->setWidget(2, QFormLayout::FieldRole, firstNLine);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName("label_6");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        lastNLine = new QLineEdit(formLayoutWidget);
        lastNLine->setObjectName("lastNLine");
        lastNLine->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lastNLine);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        gmailLine = new QLineEdit(formLayoutWidget);
        gmailLine->setObjectName("gmailLine");

        formLayout->setWidget(4, QFormLayout::FieldRole, gmailLine);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(320, 350, 161, 61));
        pushButton->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(80, 420, 131, 29));
        pushButton_2->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0) ;\n"
"font: italic 14pt \"Segoe UI\";"));
        singU->setCentralWidget(centralwidget);
        menubar = new QMenuBar(singU);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 36));
        singU->setMenuBar(menubar);
        statusbar = new QStatusBar(singU);
        statusbar->setObjectName("statusbar");
        singU->setStatusBar(statusbar);

        retranslateUi(singU);

        QMetaObject::connectSlotsByName(singU);
    } // setupUi

    void retranslateUi(QMainWindow *singU)
    {
        singU->setWindowTitle(QCoreApplication::translate("singU", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("singU", "UserName:", nullptr));
        label_2->setText(QCoreApplication::translate("singU", "Password:", nullptr));
        label_3->setText(QCoreApplication::translate("singU", "firstName:", nullptr));
        label_6->setText(QCoreApplication::translate("singU", "lastName:", nullptr));
        label_4->setText(QCoreApplication::translate("singU", "gmail:", nullptr));
        pushButton->setText(QCoreApplication::translate("singU", "sign Up", nullptr));
        pushButton_2->setText(QCoreApplication::translate("singU", "Back to Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class singU: public Ui_singU {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGU_H
