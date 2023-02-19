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




