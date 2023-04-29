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
    int xArenaEnemy=250;
    int yArenaEnemy=250;
    ArenaEnemy();
};

#endif // ARENA_H
