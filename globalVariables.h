#ifndef GLOBALS_H
#define GLOBALS_H
#include "Board.h"
#include <QVector>
#include <QPoint>
extern int modeChosen;
extern Board player1Board;
extern Board player2Board;

extern bool player1Turn; // Add this line
extern bool player2Turn; // Add this line
extern QVector<QPoint> shipBlockCoordinates;
#endif // GLOBALS_H
