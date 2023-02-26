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

class Enemy : public Player{
  public:
    int xEnemy;
    int yEnemy;
    int enemyLife;
    Enemy();

};

#endif // PLAYER_H
