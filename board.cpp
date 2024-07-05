#include "Board.h"
#include <iostream>
#include <qdebug.h>
#include <qrandom.h>
const int rows=10;
const int cols=10;
Board::Board(int size) : size(size) {
    grid.resize(size, std::vector<int>(size, 0));
}

Board::Board(const Board& other) : size(other.size), grid(other.grid) { // Copy constructor
}

std::vector<std::vector<int>>& Board::getGrid() {
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
                    for (int offsetX = -1; offsetX <= 0; ++offsetX) {
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

void Board::setAdjacenciesForBot(int id) {
    int minX = rows, minY = cols;
    int maxX = 0, maxY = 0;

    // Find the coordinates of the ship with the given id
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (this->grid[x][y] == id) {
                if (x + y < minX + minY) {
                    minX = x;
                    minY = y;
                }
                if (x + y > maxX + maxY) {
                    maxX = x;
                    maxY = y;
                }
            }
        }
    }

    // Set adjacencies around the ship
    for (int x = minX - 1; x <= maxX + 1; ++x) {
        for (int y = minY - 1; y <= maxY + 1; ++y) {
            if (x >= 0 && x < rows && y >= 0 && y < cols && this->grid[x][y] == 0) {
                this->grid[x][y] = -1;
            }
        }
    }
}

int Board::isValidStart(int x, int y, int length) {
    if (x + length > 10 || y + length > 10) {
        return -1;  // Ship placement exceeds board boundaries
    }

    if (y + length <= 10 ) {
        int counter=0;
        for (int i = 0; i < length; ++i) {
            if (this->grid[x+i][y] == 0) {
                counter++;
            }
        }
        if(counter==length)
        {
        return 1;
        }
    }
    if (x + length <= 10) {
        int counter=0;
        for (int i = 0; i < length; ++i) {
            if (this->grid[x][y+i] == 0) {
                counter++;
            }
        }
        if(counter==length)
        {
            return 0;
        }
    }


    return -1;  // Default case: Invalid ship placement
}



void Board::shuffleBoard() {
    int currentLength = 4; // Initial length (e.g., 10)

    for (int id = 10; id >= 1; --id) {
        switch (id) {
        case 10:
            currentLength = 4;
            break;
        case 9:
        case 8:
            currentLength = 3;
            break;
        case 7:
        case 6:
        case 5:
            currentLength = 2;
            break;
        case 4:
        case 3:
        case 2:
        case 1:
            currentLength = 1;
            break;
        }
        bool validStart = false;
        int startRow = 0;
        int startCol = 0;
        int state = -1;

        while (state == -1) {
            startRow = QRandomGenerator::global()->bounded(rows);
            startCol = QRandomGenerator::global()->bounded(cols);
            state = this->isValidStart(startRow, startCol, currentLength);
        }

        switch (state) {
        case 0:
            for (int i = 0; i < currentLength; ++i) {
                this->grid[startRow][startCol + i] = id;
            }
            setAdjacenciesForBot(id);
            break;

        case 1:
            for (int i = 0; i < currentLength; ++i) {
                this->grid[startRow + i][startCol] = id;
            }
            setAdjacenciesForBot(id);
            break;
        }

        // Update currentLength based on ship ID


        state = -1;
        qDebug() << "board:";
        for (int row = 0; row < rows; ++row) {
            qDebug().noquote().nospace() << this->grid[row][0] << " " << this->grid[row][1] << " "
                                         << this->grid[row][2] << " " << this->grid[row][3] << " "
                                         << this->grid[row][4] << " " << this->grid[row][5] << " "
                                         << this->grid[row][6] << " " << this->grid[row][7] << " "
                                         << this->grid[row][8] << " " << this->grid[row][9];
        }
    }
}
void Board::reset() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), 0);
    }
}












