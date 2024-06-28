#include "board.h"
#include <iostream>
Board::Board(int size: size(size)
{
    grid.resize(size,std::vector<int>(size,0));
}
bool Board::placeShip(const Ship&ship,int startX, int startY)
{
    int length = ship.getLength();
    bool isFlipped = ship.getIsFlipped();
    int id=ship.getID();
    if (isFlipped)
    {
        if (startY-length<-1)
    }
}
