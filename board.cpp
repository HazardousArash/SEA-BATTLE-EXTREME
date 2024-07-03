#include "Board.h"
#include <iostream>
#include <qdebug.h>


Board::Board(int size) : size(size)
{
    grid.resize(size, std::vector<int>(size, 0));
}
 std::vector<std::vector<int>>& Board::getGrid()  {
    return grid;  // Return the grid
}


bool Board::canPlaceShip(const Ship& ship, int startX, int startY) {
    int length = ship.getLength();
    bool isFlipped = ship.getIsFlipped();

    qDebug() << "Checking placement for ship ID:" << ship.getID() << "at (" << startX << "," << startY << ")";

    // Validate if the ship can be placed at the specified position and orientation
    if (isFlipped) {
        if (startY - length + 1 < 0) {
            qDebug() << "Cannot place ship, out of bounds (heading up)";
            return false;
        }
    } else {
        if (startX + length > size) {
            qDebug() << "Cannot place ship, out of bounds (heading right)";
            return false;
        }
    }

    // Check if the cells are available
    for (int i = 0; i < length; ++i) {
        int x = startX + (isFlipped ? 0 : i);
        int y = startY - (isFlipped ? i : 0);

        if (x < 0 || x >= size || y < 0 || y >= size) {
            qDebug() << "Cannot place ship, cell out of bounds:" << x << "," << y;
            return false;
        }

        // Check all cells the ship would occupy
        for (int j = 0; j < length; ++j) {
            int checkX = startX + (isFlipped ? 0 : j);
            int checkY = startY - (isFlipped ? j : 0);

            if (grid[checkY][checkX] != 0) {
                qDebug() << "Cannot place ship, cell already occupied:" << checkX << "," << checkY;
                return false;
            }
        }
    }

    return true; // Ship can be placed
}


void Board::placeShip(const Ship& ship, int startX, int startY) {
    int length = ship.getLength();
    bool isFlipped = ship.getIsFlipped();
    int id = ship.getID();

    qDebug() << "Placing ship with ID:" << id << "at (" << startX << "," << startY << ")";

    // Place the ship on the board, mirrored to the main diagonal
    for (int i = 0; i < length; ++i) {
        int x = startX + (isFlipped ? 0 : i);
        int y = startY - (isFlipped ? i : 0);  // Adjust for mirroring
        grid[y][x] = id;  // Swap x and y for mirroring

        qDebug() << "Placed ship part at:" << x << "," << y;
    }
}






void Board::markAdjacentCellsUnavailable(int startX, int startY, int length, bool isFlipped) {
    int dx = isFlipped ? 0 : 1;
    int dy = isFlipped ? 1 : 0;
    //not working for isFlipped=false
    for (int i = 0; i < length; ++i) {
        int x = startX + i * dx;
        int y = startY + i * dy;

        if (x >= 0 && x < size && y >= 0 && y < size && grid[y][x] >= 1 && grid[y][x] <= 10) {
            switch (length) {
            case 1:
                if (isFlipped) {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -1; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                } else {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -1; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                }
                break;

            case 2:
                if (isFlipped) {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -2; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                } else {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -2; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                }
                break;

            case 3:
                if (isFlipped) {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -3; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                } else {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -3; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                }
                break;

            case 4:
                if (isFlipped) {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -4; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                } else {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        for (int offsetY = -4; offsetY <= 1; ++offsetY) {
                            int adjX = x + offsetX;
                            int adjY = y + offsetY;
                            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                                if (grid[adjY][adjX] == 0) {
                                    grid[adjY][adjX] = -1;
                                }
                            }
                        }
                    }
                }
                break;

            default:
                break;
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




