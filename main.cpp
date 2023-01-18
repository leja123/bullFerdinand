#include <SDL.h>
#include <stdio.h>

using namespace std;

int main( int argc, char* args[] ){
	SDL_Window *window = nullptr;

	if(SDL_Init(SDL_INIT_VIDEO)<0){
        printf("Video initialisation error",SDL_GetError(),"\n");
	}
	else {
        window = SDL_CreateWindow("Bull Ferdinand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        if(window==NULL){
            printf("Window creation error",SDL_GetError(),"\n");
        }
        else {
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
