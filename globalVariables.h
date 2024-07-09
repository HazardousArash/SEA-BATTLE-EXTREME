#ifndef GLOBALS_H
#define GLOBALS_H
#include "Board.h"
#include <QVector>
#include <QPoint>
#include <QPair>
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
#endif // GLOBALS_H
