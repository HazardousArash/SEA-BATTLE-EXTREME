#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include <map>

class Ship
{
private:
    static int countOfShips;
    static int ID;
    static std::map(int, Ship> shipMap;
    int ID;
    int length;
    bool isFlipped;

public:
    Ship(int length, bool isFlipped = false);
    static void createFleet();
    //getters
    int getID() const;
    int getLength() const;
    bool getIsFlipped() const;
    static Ship getShipByID(int id);
    //setters
    void setLength(int length);
    void setIsFlipped(bool isFlipped);
    //methods
    void rotate();
    static int getCountOfShips();
    ~Ship();
};

#endif // SHIP_H
