#include "GlobalVariables.h"

int modeChosen =3; // Default to 1vs1 mode
Board player1Board(10);
Board player2Board(10);
int playerOneOil;
int playerTwoOil = 220;
bool player1Turn = true; // Define player1Turn
bool player2Turn = false; // Define player2Turn
QVector<QPoint> shipBlockCoordinates;
 int playerOneNumberOfRadars=0;
 int playerTwoNumberOfRadars=0;
int humanRadarCounts = 0;
 QPair<int, int> playerOneShieldedRows = qMakePair(-10, -10);
 QPair<int, int> playerTwoShieldedRows = qMakePair(-10, -10);
 int playerOneNumberOfGuns=0;
 int playerTwoNumberOfGuns=0;
 int playerOneNumberOfMissiles=0;
 int playerTwoNumberOfMissiles=0;
 QString globalUserName=nullptr;
 std::vector<std::vector<int>> playerOneBoard(10, std::vector<int>(10, 0));
 std::vector<std::vector<int>> playerTwoBoard(10, std::vector<int>(10, 0));
 QTcpServer* server = nullptr;
 QTcpSocket* serverSocket=nullptr;
 QTcpSocket* clientSocket = nullptr;
 QString globalHostAddress;
 bool globalIsHost = false;
 bool isOnline=true;
