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
    float xEnemy;
    float yEnemy;
    int enemyLife;
    Enemy();
    bool collision();
};

/*class Bullet : public Player{
  public:
    int xBullet;
    int yBullet;
    Bullet();
};*/

#endif // PLAYER_H
