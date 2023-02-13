#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL.h>

class Player {
    int xPlayer;
    int yPlayer;
    int playerXP;
    int playerLife;
  public:
    Player();
    void renderPlayer();
    void test();

};

#endif // PLAYER_H
