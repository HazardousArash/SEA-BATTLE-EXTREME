#include "hostmenu.h"
#include "ui_hostmenu.h"
#include <QDebug>
#include <QNetworkInterface>
#include "onlineMenu.h"
#include "globalVariables.h"
#include "gamewindow.h"

hostMenu::hostMenu(QString userName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hostMenu)
{
    ui->setupUi(this);
    this->userName = userName;

    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress& address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
            ipAddress = address.toString();
        }
    }

    QString result = "Please tell your friend to use this IP: " + ipAddress;
    ui->plainTextEdit->setPlainText(result);
    ui->plainTextEdit->appendPlainText("Waiting for the other player to connect....\n");


    server = new QTcpServer();

    connect(server, &QTcpServer::newConnection, this, &hostMenu::onNewConnection);

    if (!server->listen(QHostAddress(ipAddress), 12345)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

hostMenu::~hostMenu()
{
    delete ui;
}

void hostMenu::onNewConnection()
{
    serverSocket = server->nextPendingConnection();
    if (serverSocket) {
        ui->plainTextEdit->appendPlainText("Player connected!");
        qDebug() << "Player connected!";
        qDebug() << "serverSocket state:" << serverSocket->state();

        // Hide the current window
        this->hide();

        // Open the GameWindow
        GameWindow *gameWindow = new GameWindow();
        gameWindow->show();
    } else {
        qDebug() << "Error: Failed to get the next pending connection.";
    }
}

void hostMenu::on_pushButton_clicked()
{
    onlineMenu *newPage = new onlineMenu(userName);
    this->close();
    newPage->show();
}
