#include "GlobalVariables.h"

int modeChosen =1; // Default to 1vs1 mode
Board player1Board(10);
Board player2Board(10);
int playerOneOil = 220;
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
