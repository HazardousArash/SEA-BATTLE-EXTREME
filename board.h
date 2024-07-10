#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "ship.h"
#include "player.h"
#include "computerplayer.h"
#include <QObject>
// Forward declaration
void updateWinLoseDB(QString userName,int oil,bool isWin);
class computerPlayer;

class Board {
public:
    std::vector<std::vector<int>> grid;
    int size;

public:
    explicit Board(int size = 10);
     Board(const std::vector<std::vector<int>>& grid);
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
    void resetUnavailableCells();
    int botAi(Board& myBoard, int& selectedRow, int& selectedCol);
    bool allShipsSunken() const;
    bool isShipSunk(int shipID) const;
    bool isBotFirstMove = true;
    std::vector<std::vector<int>> multiplyBoards(const Board& other);
signals:
    void gameOver();
};

#endif // BOARD_H
