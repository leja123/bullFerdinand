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

/*bool Enemy::collision(){
    int A1=xPlayer;
    int B1=xPlayer+60;
    int C1=yPlayer;
    int D1=yPlayer+60;

    int A2=xEnemy;
    int B2=xEnemy+60;
    int C2=yEnemy;
    int D2=yEnemy+60;

    if(D1<=C2){
        cout<<"lol";
        return true;
    }

    else if(C1>=D2)
        return true;
    else if(B1<=A2)
        return true;
    else if(A1>=B2)
        return true;
    else
        return false;
}
*/
Enemy::Enemy(){
    xEnemy=rand()%(1220-0)+0;
    yEnemy=rand()%(660-0)+0;
    enemyLife=100;
}

Bullet::Bullet(){
    xBullet=xPlayer;
    yBullet=yPlayer;
}

Bull::Bull(){
    xBull=rand()%(1220-0)+0;
    yBull=rand()%(660-0)+0;
}

Door::Door(){
    xDoor=640;
    yDoor=660;
}



