#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "ship.h"
#include "player.h"
#include "computerplayer.h"

// Forward declaration
class computerPlayer;

class Board {
public:
    std::vector<std::vector<int>> grid;
    int size;

public:
    explicit Board(int size = 10);
    Board(const Board& other); // Copy constructor
    bool canPlaceShip(const Ship& ship, int startX, int startY);
    void placeShip(const Ship& ship, int startX, int startY);
    void display() const;
    void markAdjacentCellsUnavailable(int startX, int startY, int length, bool isFlipped);
    int getCell(int x, int y) const;
    void highlightAvailableBlocks(Board board);
    std::vector<std::vector<int>>& getGrid();
    void shuffleBoard();
    int isValidStart(int x, int y, int length);
    void setAdjacenciesForBot(int id);
    void reset();
};

#endif // BOARD_H
