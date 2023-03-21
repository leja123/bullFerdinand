#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "player.h"

class Game{
    public:
    Game();
    ~Game(){};
    bool init();
    void run_game();
    bool loadMedia();
    void close();


};

#endif // GAME_H_INCLUDED
