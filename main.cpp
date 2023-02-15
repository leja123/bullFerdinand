#include <SDL.h>
#include <iostream>
#include <ctime>
#include "player.h"

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

SDL_Surface* loadSurface( std::string path );
//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//background image
SDL_Surface *gBackground = NULL;

SDL_Surface *gPlayer = NULL;

SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

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
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "press.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

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

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
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

		    //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Set default current surface
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;

                            default:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }
                }
                //Apply the current image
               SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
			//render background
			SDL_BlitSurface( gBackground, NULL, gScreenSurface, NULL );
            //render player on radnom location
            SDL_Rect dest;
            dest.x = x.xPlayer;
            dest.y = x.yPlayer;
            dest.w = 60;
            dest.h = 60;
            SDL_BlitScaled( gPlayer, NULL, gScreenSurface, &dest );

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
}}
