#ifndef GLOBALS_H
#define GLOBALS_H
#include "Board.h"
#include <QVector>
#include <QPoint>
#include <QPair>
#include <QString>
#include <QTcpSocket>
#include <QTcpServer>
#include "globalVariables.h"
extern int modeChosen;
extern Board player1Board;
extern Board player2Board;
extern int playerOneOil;
extern int playerTwoOil;
extern bool player1Turn;
extern bool player2Turn;
extern QVector<QPoint> shipBlockCoordinates;
extern int playerOneNumberOfRadars;
extern int playerTwoNumberOfRadars;
extern int humanRadarCounts;
extern QPair<int, int> playerOneShieldedRows;
extern QPair<int, int> playerTwoShieldedRows;
extern int playerOneNumberOfGuns;
extern int playerTwoNumberOfGuns;
extern int playerOneNumberOfMissiles;
extern int playerTwoNumberOfMissiles;
extern QString globalUserName;
extern QTcpServer* server;
extern QTcpSocket* serverSocket;
extern QTcpSocket* clientSocket;
extern QString globalHostAddress;
extern bool globalIsHost;
extern std::vector<std::vector<int>> playerOneBoard;
extern std::vector<std::vector<int>> playerTwoBoard;
extern bool isOnline;
#endif // GLOBALS_H
