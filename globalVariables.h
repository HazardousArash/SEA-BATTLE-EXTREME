#ifndef GLOBALS_H
#define GLOBALS_H
#include "Board.h"
#include <QVector>
#include <QPoint>
extern int modeChosen;
extern Board player1Board;
extern Board player2Board;
extern int playerOneOil;
extern int playerTwoOil;
extern bool player1Turn;
extern bool player2Turn;
extern QVector<QPoint> shipBlockCoordinates;
#endif // GLOBALS_H
