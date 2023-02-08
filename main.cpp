#include <SDL.h>
#include <iostream>
#include "Game.h"

using namespace std;

Game *game = nullptr;


int main( int argc, char* args[] ){

    game = new Game();

    game->init("Bull Ferdinand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN );

    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

	/*SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Bull Ferdinand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(300); */
	return 0;
}
