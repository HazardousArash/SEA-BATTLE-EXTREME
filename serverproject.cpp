#include "serverProject.h"
#include "ui_serverProject.h"
#include <QDataStream>
#include <QDebug>

// Assuming these are declared as global variables
extern std::vector<std::vector<int>> playerOneBoard;
extern std::vector<std::vector<int>> playerTwoBoard;

serverProject::serverProject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serverProject)
{
    ui->setupUi(this);
    myServer = new QTcpServer();
    myServer->listen(QHostAddress("127.0.0.1"), 1025);
    if (!myServer->isListening()) {
        qDebug() << "Not listening..";
    } else {
        qDebug() << "Listening..";
        connect(myServer, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
    }
}

serverProject::~serverProject()
{
    delete ui;
    if (myServer) {
        myServer->close();
        delete myServer;
    }
}

void serverProject::newConnectionSlot()
{
    mySocket = myServer->nextPendingConnection();
    qDebug() << "New connected Device: " << mySocket->socketDescriptor();
    connect(mySocket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(mySocket, SIGNAL(bytesWritten(qint64)), this, SLOT(writingData()));
    connect(mySocket, SIGNAL(readyRead()), this, SLOT(readingData()));
    connect(mySocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
}

void serverProject::writingData()
{
    qDebug() << "Written successfully\n";
}

void serverProject::disconnectedFromServer()
{
    qDebug() << "Connection lost\n";
}

void serverProject::connectedToServer()
{
    qDebug() << "Connected Successfully\n";
    mySocket->write("Salam\n");
}

void serverProject::readingData()
{
    qDebug() << "Data received\n";
    QByteArray data = mySocket->readAll();
    qDebug() << "Received data: " << data;
    receiveBoards(data); // Handle receiving boards
}

void serverProject::sendBoards()
{
    QVector<QVector<int>> myVector(10, QVector<int>(10, 0)); // Initialize 10x10 vector
    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << myVector << myVector; // Send both boards (player 1 and player 2)
    mySocket->write(serializedData);
}

void serverProject::receiveBoards(const QByteArray& data)
{
    QDataStream stream(data);
    QVector<QVector<int>> player1Board, player2Board;
    stream >> player1Board >> player2Board;

    // Convert QVector<QVector<int>> to std::vector<std::vector<int>>
    serverBoard.clear();
    enemyBoard.clear();

    for (const auto& row : player1Board) {
        std::vector<int> stdRow;
        for (const auto& cell : row) {
            stdRow.push_back(cell);
        }
        serverBoard.push_back(stdRow);
    }

    for (const auto& row : player2Board) {
        std::vector<int> stdRow;
        for (const auto& cell : row) {
            stdRow.push_back(cell);
        }
        enemyBoard.push_back(stdRow);
    }

    qDebug() << "Received player 1 board:";
    for (const auto& row : player1Board) {
        qDebug() << row;
    }

    qDebug() << "Received player 2 board:";
    for (const auto& row : player2Board) {
        qDebug() << row;
    }

    // Debug output for std::vector boards
    qDebug() << "Converted std::vector player 1 board:";
    for (const auto& row : serverBoard) {
        QString rowString;
        for (const auto& cell : row) {
            rowString += QString::number(cell) + " ";
        }
        qDebug() << rowString;
    }

    qDebug() << "Converted std::vector player 2 board:";
    for (const auto& row : enemyBoard) {
        QString rowString;
        for (const auto& cell : row) {
            rowString += QString::number(cell) + " ";
        }
        qDebug() << rowString;
    }
}

void serverProject::sentData() {
    QVector<QVector<int>> player1BoardQVec;
    QVector<QVector<int>> player2BoardQVec;

    // Assuming you have playerOneBoard and playerTwoBoard as std::vector<std::vector<int>>
    for (const auto& row : playerOneBoard) {
        QVector<int> qRow;
        for (const auto& cell : row) {
            qRow.append(cell);
        }
        player1BoardQVec.append(qRow);
    }

    for (const auto& row : playerTwoBoard) {
        QVector<int> qRow;
        for (const auto& cell : row) {
            qRow.append(cell);
        }
        player2BoardQVec.append(qRow);
    }

    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << player1BoardQVec << player2BoardQVec;
    mySocket->write(serializedData);
}
