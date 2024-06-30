#include "Board.h"
#include <iostream>



Board::Board(int size) : size(size)
{
    grid.resize(size, std::vector<int>(size, 0));
}
const std::vector<std::vector<int>>& Board::getGrid() const {
    return grid;  // Return the grid
}


bool Board::placeShip(const Ship& ship, int startX, int startY)
{
    int length = ship.getLength();
    bool isFlipped = ship.getIsFlipped();
    int id = ship.getID();


    if (isFlipped)
    {
        if (startY - length + 1 <= 0) return false; //heading up
    }
    else
    {
        if (startX + length > size) return false; //heading right
    }


    for (int i = 0; i < length; ++i)
    {
        int x = startX + (isFlipped ? 0 : i);
        int y = startY - (isFlipped ? i : 0);

        // prevent segfaults
        if (x < 0 || x >= size || y < 0 || y >= size) return false;

        if (grid[x][y] != 0) return false;
    }

    // Place the ship
    for (int i = 0; i < length; ++i)
    {
        int x = startX + (isFlipped ? 0 : i);
        int y = startY - (isFlipped ? i : 0);
        grid[x][y] = id;
    }

    return true;
}

void Board::markAdjacentCellsUnavailable(int startX, int startY, int length, bool isFlipped) {
    int dx = isFlipped ? 0 : 1;
    int dy = isFlipped ? 1 : 0;

    for (int i = 0; i < length; ++i) {
        int x = startX + i * dx;
        int y = startY + i * dy;

        for (int offsetX = -1; offsetX <= 1; ++offsetX) {
            for (int offsetY = -1; offsetY <= 1; ++offsetY) {
                int adjX = x + offsetX;
                int adjY = y + offsetY;

                if (adjX > 0 && adjX <= size && adjY > 0 && adjY <= size) {
                    if (grid[adjX - 1][adjY - 1] == 0) {
                        grid[adjX - 1][adjY - 1] = -1;  // Mark as unavailable (red)
                    }
                }
            }
        }
    }
}










int Board::getCell(int x, int y) const {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return grid[x][y];
    }
    return -1; // Or any other value that indicates an invalid cell
}

void Board::display() const
{
    for (const auto& row : grid)
    {
        for (int cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}




