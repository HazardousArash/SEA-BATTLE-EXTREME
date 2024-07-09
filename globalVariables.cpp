#include "GlobalVariables.h"

int modeChosen =2; // Default to 1vs1 mode
Board player1Board(10);
Board player2Board(10);
int playerOneOil = 220;
int playerTwoOil = 220;
bool player1Turn = true; // Define player1Turn
bool player2Turn = false; // Define player2Turn
QVector<QPoint> shipBlockCoordinates;
