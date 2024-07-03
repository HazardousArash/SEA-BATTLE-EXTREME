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
    bool canPlaceShip(const Ship& ship, int startX, int startY);
    void placeShip(const Ship& ship, int startX, int startY);
    void display() const;
    void markAdjacentCellsUnavailable(int startX, int startY, int length, bool isFlipped);
    int getCell(int x, int y) const ;
    void highlightAvailableBlocks(Board board);
     std::vector<std::vector<int>>& getGrid() ;
};

#endif // BOARD_H
