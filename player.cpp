#include <iostream>
#include "player.h"

using namespace std;

Player::Player(){
    xPlayer=rand()%(1280-0)+0;
    yPlayer=rand()%(720-0)+0;
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

