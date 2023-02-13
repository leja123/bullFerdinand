#include <SDL.h>
#include <iostream>
#include <ctime>
#include "player.h"

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//background image
SDL_Surface *gBackground = NULL;

SDL_Surface *gPlayer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout<<"SDL could not initialize! SDL_Error: \n"<< SDL_GetError();
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Bull Ferdinand", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			cout<<"Window could not be created! SDL_Error: \n"<<SDL_GetError();
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gBackground = SDL_LoadBMP( "bg.bmp" );
	if( gBackground == NULL )
	{
		cout<<"Unable to load image %s! SDL Error: \n"<< "bg.bmp"<< SDL_GetError();
		success = false;
	}

    gPlayer=SDL_LoadBMP("player.bmp");


	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gBackground );
	gBackground = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}




int main( int argc, char* args[] )
{
    srand(time(NULL));
    Player x;
	//Start up SDL and create window
	if( !init() )
	{
		cout<<"Failed to initialize!\n";
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			cout<<"Failed to load media!\n";
		}
		else
		{
			//Apply the image
			SDL_BlitSurface( gBackground, NULL, gScreenSurface, NULL );
            SDL_BlitSurface( gPlayer, NULL, gScreenSurface, NULL );
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );
            x.test();
            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
