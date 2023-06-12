#ifndef ARENA_H
#define ARENA_H

class Arena {
  public:
    int xArena;
    int yArena;
    Arena();
};

class ArenaEnemy : public Arena {
  public:
    float xArenaEnemy;
    float yArenaEnemy;
    int arenaEnemyLife;
    ArenaEnemy();
};

#endif // ARENA_H
