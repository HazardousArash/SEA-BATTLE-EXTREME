#include "clientmenu.h"
#include "ui_clientmenu.h"
#include "onlinemenu.h"
#include "globalVariables.h"  // Include the global variables header

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

    // Initialize the client socket
    clientSocket = new QTcpSocket(this);

    // Connect the socket signals
    connect(clientSocket, &QTcpSocket::connected, this, &clientMenu::onConnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &clientMenu::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &clientMenu::onDisconnected);

    // Connect to the server
    clientSocket->connectToHost(globalHostAddress, 12345);
}

// Slot to handle successful connection
void clientMenu::onConnected()
{
    qDebug() << "Connected to server.";
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
