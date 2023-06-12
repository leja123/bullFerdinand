#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "player.h"
#include <cstring>

class Game{
    public:
    Game();
    ~Game(){};
    char name[21];
    bool init();
    void menu();
    void run_game();
    void pause();
    void hidePauseScreen();
    void replay();
    void leaderboard();
    bool loadMedia();
    void close();
};

#endif // GAME_H_INCLUDED
