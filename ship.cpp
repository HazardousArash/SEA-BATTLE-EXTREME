#include "ship.h"

//static members...
int Ship::countOfShips=0;
int Ship::nextID=1;
std::map<int,Ship> Ship::shipMap;
Ship::Ship(int length, bool isFlipped) : length(length), isFlipped(isFlipped)
{
    ID=nextID++;
    countOfShips++;
    shipMap[ID] = *this;
}
Ship::~Ship()
{
    countOfShips--;
    shipMap.erase(ID);
}
// creating a fleet...
void Ship::createFleet()
{
    // length 1 ships
    for(int i=0;i<4;++i)
    {
        Ship ship(1);
    }
    // length 2 ships
    for(int i=0;i<3;++i)
    {
        Ship ship(2);
    }
    // length 3 ships
    for(int i=0;i<2;++i)
    {
        Ship ship(3);
    }
    // length 4 ships
    for(int i=0;i<1;++i)
    {
        Ship ship(4);
    }
}
//getters...
int Ship::getID() const
{
    return ID;
}
int Ship::getLength() const
{
    return length;
}
bool Ship::getIsFlipped() const
{
    return isFlipped;
}
Ship Ship::getShipByID() const
{
    return shipMap.at(id);
}
//setters...
void Ship::setLength(int length)
{
    this->length=length;
}
void Ship::setIsFlipped(bool isFlipped)
{
    this->isFlipped = isFlipped;
}
//methods...
void Ship::rotate()
{
    isFlipped=!isFlipped;
}
int Ship::getCountOfShips()
{
    return countOfShips;
}
