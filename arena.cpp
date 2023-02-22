#include <iostream>
#include "arena.h"

using namespace std;


Arena::Arena(){
    xArena=rand()%(980-0)+0;
    yArena=rand()%(520-0)+0;

}

Enemy::Enemy(){
    xEnemy=rand()%(1220-0)+0;
    yEnemy=rand()%(660-0)+0;
}
