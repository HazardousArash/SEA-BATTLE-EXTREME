#include "clientProject.h"
#include "globalVariables.h" // Include this to access the global variables
#include <QDataStream>
#include <QDebug>

// Utility functions for conversion between std::vector and QVector
template<typename T>
QVector<T> toQVector(const std::vector<T>& stdVector) {
    QVector<T> qVector;
    for (const auto& element : stdVector) {
        qVector.append(element);
    }
    return qVector;
}

template<typename T>
std::vector<T> toStdVector(const QVector<T>& qVector) {
    std::vector<T> stdVector;
    for (const auto& element : qVector) {
        stdVector.push_back(element);
    }
    return stdVector;
}

clientProject::clientProject(QWidget *parent)
    : QWidget(parent),
    socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &clientProject::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &clientProject::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &clientProject::onDisconnected);

    socket->connectToHost("127.0.0.1", 1025);
}

clientProject::~clientProject()
{
    delete socket;
}

void clientProject::onConnected()
{
    qDebug() << "Connected to server.";
    sendBoards();
}

void clientProject::onReadyRead()
{
    QByteArray receivedData = socket->readAll();
    qDebug() << "Data received";
    processReceivedData(receivedData);
}

void clientProject::onSendData()
{
    qDebug() << "Sending data to server.";

    QVector<QVector<int>> player1BoardQVec;
    QVector<QVector<int>> player2BoardQVec;

    // Assuming you have playerOneBoard and playerTwoBoard as std::vector<std::vector<int>>
    for (const auto& row : playerOneBoard) {
        player1BoardQVec.append(toQVector(row));
    }

    for (const auto& row : playerTwoBoard) {
        player2BoardQVec.append(toQVector(row));
    }

    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << player1BoardQVec << player2BoardQVec;
    socket->write(serializedData);
}


void clientProject::onDisconnected()
{
    qDebug() << "Disconnected from server.";
}

void clientProject::processReceivedData(const QByteArray& data)
{
    QDataStream stream(data);
    QVector<QVector<int>> player1Board, player2Board;
    stream >> player1Board >> player2Board;

    qDebug() << "Received player 1 board:";
    for (const auto& row : player1Board) {
        qDebug() << row;
    }

    qDebug() << "Received player 2 board:";
    for (const auto& row : player2Board) {
        qDebug() << row;
    }

    // Convert QVector<QVector<int>> to std::vector<std::vector<int>>
    std::vector<std::vector<int>> stdPlayer1Board, stdPlayer2Board;

    for (const auto& row : player1Board) {
        stdPlayer1Board.push_back(toStdVector(row));
    }

    for (const auto& row : player2Board) {
        stdPlayer2Board.push_back(toStdVector(row));
    }

    // Debug output for std::vector boards
    qDebug() << "Converted std::vector player 1 board:";
    for (const auto& row : stdPlayer1Board) {
        QString rowString;
        for (const auto& cell : row) {
            rowString += QString::number(cell) + " ";
        }
        qDebug() << rowString;
    }

    qDebug() << "Converted std::vector player 2 board:";
    for (const auto& row : stdPlayer2Board) {
        QString rowString;
        for (const auto& cell : row) {
            rowString += QString::number(cell) + " ";
        }
        qDebug() << rowString;
    }
}

void clientProject::sendBoards()
{
    QVector<QVector<int>> player1BoardQVec;
    QVector<QVector<int>> player2BoardQVec;

    // Assuming you have playerOneBoard and playerTwoBoard as std::vector<std::vector<int>>
    for (const auto& row : playerOneBoard) {
        player1BoardQVec.append(toQVector(row));
    }

    for (const auto& row : playerTwoBoard) {
        player2BoardQVec.append(toQVector(row));
    }

    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << player1BoardQVec << player2BoardQVec;
    socket->write(serializedData);
}
