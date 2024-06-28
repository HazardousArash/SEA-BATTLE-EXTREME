#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "ship.h"

class Board
{
private:
    std::vector<std::vector<int>> grid;
    int size;
public:
    Board(int size = 10);
    bool placeShip(const Ship& ship, int startX, int startY);
    void display() const;
};

#endif // BOARD_H
