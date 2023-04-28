#include <SDL.h>
#include <iostream>
#include <ctime>
#include "player.h"
#include "arena.h"
#include "game.h"


using namespace std;


Game *game = nullptr;

/*
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();
*/

int main( int argc, char* args[] )
{
   game = new Game();
   game->run_game();
   //game->menu();
    //game->pause();
	return 0;
}
