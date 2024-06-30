#include "Ship.h"

int Ship::countOfShips = 0;
int Ship::nextID = 1;
std::map<int, Ship*> Ship::shipMap;

Ship::Ship() : ID(0), length(0), isFlipped(true), isSunken(false) {}

Ship::Ship(int length, bool isFlipped, bool isSunken)
    : length(length), isFlipped(isFlipped), isSunken(isSunken) {
    ID = nextID++;
    countOfShips++;
    shipMap[ID] = this;
}

Ship::~Ship() {
    countOfShips--;
    shipMap.erase(ID);
}

std::map<int, Ship*> Ship::getAllShips() {
    return shipMap;
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
Ship* Ship::getShipByID(int id) {
    auto it = shipMap.find(id);
    if (it != shipMap.end()) {
        return it->second; // Return the pointer
    }
    return nullptr; // Handle case if ID is not found
}
bool Ship::getIsSunken()const
{
    return isSunken;
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
void Ship::setIsSunken(bool isSunken)
{
    this->isSunken= isSunken;
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
