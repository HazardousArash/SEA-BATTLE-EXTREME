#include "clientmenu.h"
#include "ui_clientmenu.h"
#include "onlinemenu.h"
#include "globalVariables.h"
#include <QDebug>

clientMenu::clientMenu(QString userName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::clientMenu)
{
    ui->setupUi(this);
    this->userName = userName;
}

clientMenu::~clientMenu()
{
    delete ui;
}

void clientMenu::on_pushButton_clicked()
{
    onlineMenu *newPage = new onlineMenu(userName);
    this->close();
    newPage->show();
}

void clientMenu::on_pushButton_2_clicked()
{
    globalHostAddress = ui->lineEdit->text();

    // Initialize the global client socket
    clientSocket = new QTcpSocket(this);

    // Connect the socket signals
    connect(clientSocket, &QTcpSocket::connected, this, &clientMenu::onConnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &clientMenu::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &clientMenu::onDisconnected);

    // Connect to the server
    qDebug() << "Attempting to connect to host at" << globalHostAddress;
    clientSocket->connectToHost(globalHostAddress, 12345);
}

// Slot to handle successful connection
void clientMenu::onConnected()
{
    qDebug() << "Connected to server.";
    qDebug() << "clientSocket state:" << clientSocket->state();

    // Start the game for the client
    GameWindow *gameWindow = new GameWindow();
    gameWindow->show();
    this->close();
}

// Slot to handle incoming data
void clientMenu::onReadyRead()
{
    QByteArray receivedData = clientSocket->readAll();
    // Process the received data
    qDebug() << "Data received from server:" << receivedData;
}

// Slot to handle disconnection
void clientMenu::onDisconnected()
{
    qDebug() << "Disconnected from server.";
}
