#include "hostmenu.h"
#include "ui_hostmenu.h"
#include <QDebug>
#include <QNetworkInterface>
#include "onlineMenu.h"
#include "globalVariables.h"  // Include the global variables header
#include "gamewindow.h"       // Include the GameWindow header

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

    // Initialize the global serverSocket
    serverSocket = new QTcpServer(this);

    connect(serverSocket, &QTcpServer::newConnection, this, &hostMenu::onNewConnection);

    if (!serverSocket->listen(QHostAddress::Any, 12345)) {
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
    clientSocket = serverSocket->nextPendingConnection();
    if (clientSocket) {
        ui->plainTextEdit->appendPlainText("Player connected!");
        qDebug() << "Player connected!";

        // Hide the current window
        this->hide();

        // Open the GameWindow
        GameWindow *gameWindow = new GameWindow();
        gameWindow->show();
    }
}

void hostMenu::on_pushButton_clicked()
{
    onlineMenu *newPage = new onlineMenu(userName);
    this->close();
    newPage->show();
}
