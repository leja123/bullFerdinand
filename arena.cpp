#include <iostream>
#include "arena.h"

using namespace std;


Arena::Arena(){
    xArena=rand()%(980-0)+0;
    yArena=rand()%(520-0)+0;

}

ArenaEnemy::ArenaEnemy(){
    arenaEnemyLife=100;
    xArenaEnemy=xArena+rand()%10+0;
    yArenaEnemy=yArena+rand()%10+0;
}

