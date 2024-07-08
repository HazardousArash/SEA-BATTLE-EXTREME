#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"
#include <string>

class ComputerPlayer: public Player
{
    int difficulty;
    std::string name;
    int level;
    std::string code;
public:
    ComputerPlayer();

};

#endif // COMPUTERPLAYER_H
