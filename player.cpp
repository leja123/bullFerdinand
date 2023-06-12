#include <iostream>
#include "player.h"

using namespace std;

Player::Player(){
    xPlayer=rand()%(1220-0)+0;
    yPlayer=rand()%(660-0)+0;
    playerXP=0;
    playerLife=100;

}

void Player::test(){
    cout<<xPlayer<<" "<<yPlayer<<" "<<playerXP<<" "<<playerLife;
}

void Player::offScreen(){
    if(xPlayer<=0)
        xPlayer=0;
    if(xPlayer>=1220)
        xPlayer=1220;
    if(yPlayer<=0)
        yPlayer=0;
    if(yPlayer>=660)
        yPlayer=660;
}

Enemy::Enemy(){
    xEnemy=rand()%(1220-0)+0;
    yEnemy=rand()%(660-0)+0;
    enemyLife=100;
}

Bullet::Bullet(){
    xBullet=0;
    yBullet=0;
}

Bull::Bull(){
    xBull=rand()%(1220-0)+0;
    yBull=rand()%(660-0)+0;
}

Door::Door(){
    xDoor=640;
    yDoor=660;
}



