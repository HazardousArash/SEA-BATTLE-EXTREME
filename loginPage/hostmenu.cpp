#include "hostmenu.h"
#include "ui_hostmenu.h"
#include <QDebug>
#include <QNetworkInterface>
#include "onlineMenu.h"

hostMenu::hostMenu(QString userName,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hostMenu)
{
    ui->setupUi(this);
    this->userName=userName;
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress& address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
            ipAddress=address.toString();
        }
    }
    QString result="Please tell your friend to use this ip :"+ipAddress;
    ui->plainTextEdit->setPlainText(result);
    ui->plainTextEdit->appendPlainText("Waiting for the other player to connect....\n");
}

hostMenu::~hostMenu()
{
    delete ui;
}

void hostMenu::on_pushButton_clicked()
{
    onlineMenu *newPage=new onlineMenu(userName);
    this->close();
    newPage->show();
}

