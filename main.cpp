#include <SDL.h>
#include <iostream>
#include <ctime>
#include "player.h"
#include "arena.h"
#include "game.h"


using namespace std;

Game *game = nullptr;

int main( int argc, char* args[] )
{
   game = new Game();
   game->menu();
	return 0;
}
