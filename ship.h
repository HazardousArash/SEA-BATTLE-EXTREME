#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <map>
#include <memory>

class Ship {
public:
    Ship();
    //Ship(int length, bool isFlipped = true, bool isSunken = false);
    Ship(int length);
    ~Ship();

    bool isValid() const;

    // Static methods
    static std::map<int, Ship*> getAllShips();
    static void createFleet();
    static Ship* getShipByID(int id);
    static int getCountOfShips();

    // Getters
    int getID() const;
    int getLength() const;
    bool getIsFlipped() const;
    bool getIsSunken() const;
    int getStartX() const { return startX; }
    int getStartY() const { return startY; }
    // Setters
    void setLength(int length);
    void setIsFlipped(bool isFlipped);
    void setIsSunken(bool isSunken);
    void setStartX(int x) { startX = x; }
    void setStartY(int y) { startY = y; }

    // Methods
    void rotate();

private:
    static int countOfShips;
    static int nextID;
    static std::map<int, Ship*> shipMap;
    int startX;
    int startY;
    int ID;
    int length;
    bool isFlipped;
    bool isSunken;
};

#endif // SHIP_H
