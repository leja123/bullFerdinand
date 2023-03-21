#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class Game{
    public:
    Game();
    ~Game(){};
    bool init();
    bool loadMedia();
    void close();

};

#endif // GAME_H_INCLUDED
