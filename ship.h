#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <map>
#include <memory>

class Ship {
public:
    Ship();
    Ship(int length, bool isFlipped = true, bool isSunken = false);
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

    // Setters
    void setLength(int length);
    void setIsFlipped(bool isFlipped);
    void setIsSunken(bool isSunken);

    // Methods
    void rotate();

private:
    static int countOfShips;
    static int nextID;
    static std::map<int, Ship*> shipMap;

    int ID;
    int length;
    bool isFlipped;
    bool isSunken;
};

#endif // SHIP_H
