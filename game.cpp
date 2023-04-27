#include <iostream>
#include "game.h"
#include "player.h"
#include "arena.h"
#include <SDL.h>
#include <ctime>

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
    KEY_PRESS_SURFACE_SPACE,
    KEY_PRESS_SURFACE_TOTAL

};

SDL_Surface* loadSurface( std::string path );
//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//background image
SDL_Surface *gMenuBackground = NULL;

SDL_Surface *gBackground = NULL;

SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface *gPlayer = NULL;

SDL_Surface *gBullet = NULL;

SDL_Surface *gArena = NULL;

SDL_Surface *gEnemy = NULL;

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        cout<<"Unable to load image %s! SDL Error: \n"<<path.c_str()<<SDL_GetError();
    }

    return loadedSurface;
}



Game::Game(){
}

void Game::menu(){
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
		    while(true){
                SDL_BlitSurface( gMenuBackground, NULL, gScreenSurface, NULL );

            SDL_UpdateWindowSurface( gWindow );
		    }






		}
		close();
	}

}

/*Game::~Game(){

}*/
void Game::run_game(){
srand(time(NULL));
    Player x;
    Arena y[5];
    Enemy z[2];
    Bullet w[5];


    bool bulletShow=false;

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
            gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

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
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                                x.yPlayer-=10;
                                x.offScreen();
                                break;

                            case SDLK_DOWN:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                                x.yPlayer+=10;
                                x.offScreen();
                                break;

                            case SDLK_LEFT:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                                x.xPlayer-=10;
                                x.offScreen();
                                break;

                            case SDLK_RIGHT:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                                x.xPlayer+=10;
                                x.offScreen();
                                break;
                            case SDLK_SPACE:
                                bulletShow=true;
                                //bullet goes towards enemy
                                for(int i=0; i<10; i++){
                                    if(w[1].xBullet>z[1].xEnemy)
                                        w[1].xBullet--;
                                    else
                                        w[1].xBullet++;
                                    if(w[1].yBullet>z[1].yEnemy)
                                        w[1].yBullet--;
                                    else
                                        w[1].yBullet++;

                                        if(bulletShow){
                                            SDL_Rect destB;
                                            destB.x = w[1].xBullet;
                                            destB.y = w[1].yBullet;
                                            destB.w = 60;
                                            destB.h = 60;
                                            SDL_BlitScaled( gBullet, NULL, gScreenSurface, &destB );
                                        }
                                }




                                break;

                            default:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                                x.offScreen();
                                break;
                        }
                        /*if(e.key.keysym.sym==SDLK_SPACE)
                            for(int i=0; i<5; i++){
                                if(e.key.keysym.sym==SDLK_SPACE){
                                SDL_Rect destB;
                                destB.x = w[i].xBullet;
                                destB.y = w[i].yBullet;
                                destB.w = 60;
                                destB.h = 60;
                                SDL_BlitScaled( gBullet, NULL, gScreenSurface, &destB );

                                }
                                while(w[i].xBullet<=SCREEN_WIDTH){
                                    w[i].xBullet++;
                                }
                            }*/

                    }
                }
                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
			//render background
			SDL_BlitSurface( gBackground, NULL, gScreenSurface, NULL );


			//renders arenas if player is less than 100px away
			for(int i=0; i<5; i++){
                if(x.xPlayer<y[i].xArena+400 && x.xPlayer>y[i].xArena-100 && x.yPlayer<y[i].yArena+300 && x.yPlayer>y[i].yArena-100 ){
                SDL_Rect destA;
                destA.x = y[i].xArena;
                destA.y = y[i].yArena;
                destA.w = 300;
                destA.h = 200;
                SDL_BlitScaled( gArena, NULL, gScreenSurface, &destA );
                }
			}

			//render bullet
			if(bulletShow){
                SDL_Rect destB;
                destB.x = w[1].xBullet;
                destB.y = w[1].yBullet;
                destB.w = 60;
                destB.h = 60;
                SDL_BlitScaled( gBullet, NULL, gScreenSurface, &destB );
			}

            //render player on random location
            SDL_Rect dest;
            dest.x = x.xPlayer;
            dest.y = x.yPlayer;
            dest.w = 60;
            dest.h = 60;
            SDL_BlitScaled( gPlayer, NULL, gScreenSurface, &dest );

            /*for(int i=0; i<5; i++){
                if(e.key.keysym.sym==SDLK_SPACE){
                SDL_Rect destB;
                destB.x = w[i].xBullet;
                destB.y = w[i].yBullet;
                destB.w = 60;
                destB.h = 60;
                SDL_BlitScaled( gPlayer, NULL, gScreenSurface, &destB );
                }
            }*/



            bool col=false;
            //bool colEnemy=false;
            //render enemies
            for(int i=0; i<2; i++){
                SDL_Rect destE;
                destE.x = z[i].xEnemy;
                destE.y = z[i].yEnemy;
                destE.w = 60;
                destE.h = 60;
                SDL_BlitScaled( gEnemy, NULL, gScreenSurface, &destE );
                //chases player if less than 200px away

                //collisiion
                int A2=x.xPlayer;
                int B2=x.xPlayer+60;
                int C2=x.yPlayer;
                int D2=x.yPlayer+60;

                int A1=z[i].xEnemy;
                int B1=z[i].xEnemy+60;
                int C1=z[i].yEnemy;
                int D1=z[i].yEnemy+60;

                if(x.xPlayer<z[i].xEnemy+200 && x.xPlayer>z[i].xEnemy-200 && x.yPlayer<z[i].yEnemy+200 && x.yPlayer>z[i].yEnemy-200){
                if(D1<=C2)
                    col=true;
                if(C1>=D2)
                    col=true;
                if(B1<=A2)
                    col=true;
                if(A1>=B2)
                    col=true;
                }


                /*for(int i=0; i<2; i++){
                    for(int j=i+1; j<2; j++){
                        if(z[i].xEnemy < z[j].xEnemy+60 &&
                           z[i].xEnemy+60 > z[j].xEnemy&&
                           z[i].yEnemy < z[j].yEnemy+60 &&
                           z[i].yEnemy+60 > z[j].xEnemy)
                            colEnemy= true;
                        else
                            colEnemy=false;
                    }
                }*/


                if(z[i].xEnemy+200 && x.xPlayer>z[i].xEnemy-200 && x.yPlayer<z[i].yEnemy+200 && x.yPlayer>z[i].yEnemy-200 && col ){ //!colEnemy
                    if(z[i].xEnemy>x.xPlayer)
                        z[i].xEnemy-=0.5;
                    else
                        z[i].xEnemy+=0.5;
                    if(z[i].yEnemy>x.yPlayer)
                        z[i].yEnemy-=0.5;
                    else
                        z[i].yEnemy+=0.5;
                }


            }

		}
	}

	//Free resources and close SDL
	close();
}
}

bool Game::init(){
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

bool Game::loadMedia()
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

	gMenuBackground = SDL_LoadBMP( "menubg.bmp" );
	if( gMenuBackground == NULL )
	{
		cout<<"Unable to load image %s! SDL Error: \n"<< "bg.bmp"<< SDL_GetError();
		success = false;
	}

    gArena=SDL_LoadBMP("arena.bmp");

    gEnemy=SDL_LoadBMP("enemy.bmp");

    gBullet=SDL_LoadBMP("bullet.bmp");

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "default.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        cout<<"Failed to load default image!\n";
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        cout<<"Failed to load up image!\n";
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        cout<<"Failed to load down image!\n";
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        cout<<"Failed to load left image!\n";
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        cout<<"Failed to load right image!\n";
        success = false;
    }

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_SPACE ] = loadSurface( "bullet.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_SPACE ] == NULL )
    {
        cout<<"Failed to load default image!\n";
        success = false;
    }

	return success;
}

void Game::close()
{
    SDL_FreeSurface( gMenuBackground );
	gBackground = NULL;
	//Deallocate surface
	SDL_FreeSurface( gBackground );
	gBackground = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


