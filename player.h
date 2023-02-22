#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL.h>

class Player {
  public:
    int xPlayer;
    int yPlayer;
    int playerXP;
    int playerLife;
    Player();
    void renderPlayer();
    void test();
    void offScreen();
};

#endif // PLAYER_H
