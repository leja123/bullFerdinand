#include <iostream>
#include "game.h"
#include "player.h"
#include "arena.h"
#include <SDL.h>
#include <ctime>
#include <cstring>
#include <fstream>

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
    KEY_PRESS_SURFACE_ESCAPE,
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

SDL_Surface *gPause = NULL;

SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface *gPlayer = NULL;

SDL_Surface *gBullet = NULL;

SDL_Surface *gArena = NULL;

SDL_Surface *gEnemy = NULL;

SDL_Surface *gArenaEnemy = NULL;

SDL_Surface *gBull = NULL;

SDL_Surface *gDoor = NULL;

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

Bull *bull = NULL;
Bullet *bullet = NULL;
Arena *arena = NULL;
Enemy *enemy = NULL;
ArenaEnemy *arenaEnemy = NULL;
Door *door = NULL;

struct leaderboardEntry {
    char playerName[21];
    int points;
};

struct Coordinates {
    int cX;
    int cY;
};

void addToLeaderboard(struct leaderboardEntry x){
    struct leaderboardEntry a;
    bool z=true;
    ofstream out("tmp.bin", ios::binary);
    ifstream in("leaderboard.bin", ios::binary);
    if(!in.is_open())
        cout<<"File doesn't exist";
    else{
        while(in.read((char*)&a, sizeof(a))){
            if(z && (a.points < x.points)){
                out.write((char*)&x, sizeof(x));
                z=false;
            }
            out.write((char*)&a, sizeof(a));
        }
        if(z){
            out.write((char*)&x, sizeof(x));
            cout<<endl<<x.playerName<<" "<<x.points<<endl;
        }
    }
    out.close();
    in.close();
    remove("leaderboard.bin");
    rename("tmp.bin", "leaderboard.bin");
}

void showLeaderboard(){
    struct leaderboardEntry a;
    ifstream read("leaderboard.bin", ios::binary);
    if (read.is_open()) {
        cout<<endl<<endl<< "Leaderboard:\n";
        int c = 0;
        while (c < 5 && read.read((char*)&a, sizeof(a))) {
            cout << a.playerName << " " << a.points << endl;
            c++;
        }

        if (c == 0) {
            cout << "File is empty";
        }
    } else {
        cout << "File not found";
    }

}

Game::Game(){

}

void Game::pause(){
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

            while(1){


                SDL_BlitSurface( gPause, NULL, gScreenSurface, NULL );
                SDL_UpdateWindowSurface( gWindow );
                bool quit=false;
                SDL_Event e;
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
                            case SDLK_ESCAPE:
                                hidePauseScreen();
                                break;
                        }
                    }
                }
            }

            }

            }
            close();
        }
}

void Game::leaderboard(){
    struct leaderboardEntry x;
    strcpy(x.playerName, name );
    x.points=0;
    cout<<x.playerName<<" "<<x.points;
    addToLeaderboard(x);
    showLeaderboard();
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
            SDL_BlitSurface( gMenuBackground, NULL, gScreenSurface, NULL );

            SDL_UpdateWindowSurface( gWindow );
            //bool quit = false;
            bool repeat=true;
            int x;
            while(repeat){
                cin>>x;
                ofstream data;
                switch(x)
                {
                    case 1:
                        cin.ignore();
                        fgets(name, 21, stdin);
                        cout<<"Hello "<<name;
                        break;
                    case 2:
                        repeat=false;
                        pause();
                        break;
                    case 3:
                        leaderboard();
                        break;
                    case 4:
                        replay();
                        break;
                    case 5:
                        repeat=false;
                        run_game();
                    break;
                }

            }

            bool closewindow=false;
            while(!closewindow){
            SDL_BlitSurface( gMenuBackground, NULL, gScreenSurface, NULL );

            SDL_UpdateWindowSurface( gWindow );
        }

        }
    }

		close();
}


void savePlayerPosition(int &x, int &y) {
    struct Coordinates tmp;
    tmp.cX=x;
    tmp.cY=y;
    ofstream outFile("player_position.bin", ios::binary | ios::app);
    outFile.write((char*)&tmp, sizeof(tmp));
    outFile.close();

}



void Game::replay() {
    if (!init()) {
            cout << "Failed to initialize!\n";
            return;
        }
        else {
             if (!loadMedia()) {
            cout << "Failed to load media!\n";
            return;
        }
        else {

        while (true) {
            SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);

            struct Coordinates tmp;
            ifstream inFile("player_position.bin", ios::binary);
            if(!inFile.is_open()){
                cout<<"Not open";
            }
            else {
                while(inFile.read((char*)&tmp, sizeof(tmp))){

                SDL_Rect destReplay;
                destReplay.x = tmp.cX;
                destReplay.y = tmp.cY;
                destReplay.w = 60;
                destReplay.h = 60;


                SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
                SDL_BlitScaled(gPlayer, NULL, gScreenSurface, &destReplay);

                SDL_UpdateWindowSurface(gWindow);


                SDL_Delay(50);
            }

           }
        }
        }

    }
}









void Game::run_game(){
srand(time(NULL));
    Player x;
    int totalKills=0;
    int killCount=0;
    int arenaCount=0;
    int arenaEnemyKillCount=0;
    int level=1;
    bool showArena=false;
    bool battleBegin=false;
    bool showBull=false;
    bool bullIsSafe=false;
    enemy = new Enemy();
    arena = new Arena();
    arenaEnemy = new ArenaEnemy();

    bool bulletShow=false;
    bool firstShoot=true;

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
                                savePlayerPosition(x.xPlayer, x.yPlayer);
                                break;

                            case SDLK_DOWN:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                                x.yPlayer+=10;
                                x.offScreen();
                                savePlayerPosition(x.xPlayer, x.yPlayer);
                                break;

                            case SDLK_LEFT:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                                x.xPlayer-=10;
                                x.offScreen();
                                savePlayerPosition(x.xPlayer, x.yPlayer);
                                break;

                            case SDLK_RIGHT:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                                x.xPlayer+=10;
                                x.offScreen();
                                savePlayerPosition(x.xPlayer, x.yPlayer);
                                break;
                            case SDLK_SPACE:
                                bulletShow=true;
                                //first shoot je zatu de da bulletu pleyerjeve kordinate
                                if(firstShoot){
                                    bullet = new Bullet;
                                    bullet->xBullet=x.xPlayer;
                                    bullet->yBullet=x.yPlayer;
                                    firstShoot=false;

                                }
                                if(battleBegin){
                                        for(int i=0; i<50; i++){
                                            if(bullet->xBullet>arenaEnemy->xArenaEnemy)
                                                bullet->xBullet--;
                                            else
                                                bullet->xBullet++;
                                            if(bullet->yBullet>arenaEnemy->yArenaEnemy)
                                                bullet->yBullet--;
                                            else
                                                bullet->yBullet++;
                                            }
                                }
                                else{
                                    for(int i=0; i<50; i++){
                                    if(bullet->xBullet>enemy->xEnemy)
                                        bullet->xBullet--;
                                    else
                                        bullet->xBullet++;
                                    if(bullet->yBullet>enemy->yEnemy)
                                        bullet->yBullet--;
                                    else
                                        bullet->yBullet++;
                                    }
                                        if(bulletShow){
                                            SDL_Rect destB;
                                            destB.x = bullet->xBullet;
                                            destB.y = bullet->yBullet;
                                            destB.w = 60;
                                            destB.h = 60;
                                            SDL_BlitScaled( gBullet, NULL, gScreenSurface, &destB );
                                        }
                                }
                                //ce je battle begin true pal strejle sam une arena enemije
                                if(battleBegin){
                                    if(bullet->xBullet<arenaEnemy->xArenaEnemy+60 && bullet->xBullet>arenaEnemy->xArenaEnemy-60 && bullet->yBullet<arenaEnemy->yArenaEnemy+60 && bullet->yBullet>arenaEnemy->yArenaEnemy-60){
                                        arenaEnemy->arenaEnemyLife-=25;
                                        if(arenaEnemy->arenaEnemyLife==0){
                                            arenaEnemyKillCount++;
                                            totalKills++;
                                            delete arenaEnemy;
                                            //ce je prvi level sa 3 enemi ce je pa drugi level ih je pa 5
                                            if((arenaEnemyKillCount<3&&level==1) || (arenaEnemyKillCount<5&&level==2)){
                                                arenaEnemy = new ArenaEnemy();
                                            }
                                            else{
                                                delete arena;
                                                arenaCount++;
                                                arenaEnemyKillCount=0;
                                                battleBegin=false;
                                                showArena=false;
                                                //new level
                                                if(arenaCount>=5){
                                                    level++;
                                                    arenaCount=0;
                                                    delete arenaEnemy;
                                                    delete bullet;
                                                    firstShoot=true;
                                                    bull = new Bull();
                                                    door = new Door();
                                                    showBull=true;
                                                    }
                                                if(level<3){
                                                    arena = new Arena();
                                                arenaEnemy = new ArenaEnemy();
                                                }
                                                else{ //kanc igre
                                                    struct leaderboardEntry tmp;
                                                    strcpy(tmp.playerName, name);
                                                    tmp.points=totalKills;
                                                    addToLeaderboard(tmp);
                                                    showLeaderboard();
                                                    replay();
                                                    /*ofstream data;
                                                    data.open("scores.txt");
                                                    data<<totalKills;
                                                    data.close();
                                                    replay();*/
                                                }

                                        }
                                    }
                                    delete bullet;
                                    firstShoot=true;
                                    bulletShow=false;
                                    }
                                }
                                //ce je battlebegin false (strejle ta druge enemije)
                                else {
                                    if(bullet->xBullet<enemy->xEnemy+60 && bullet->xBullet>enemy->xEnemy-60 && bullet->yBullet<enemy->yEnemy+60 && bullet->yBullet>enemy->yEnemy-60){
                                    enemy->enemyLife-=25;
                                    if(enemy->enemyLife==0){
                                        killCount++;
                                        totalKills++;
                                        delete enemy;
                                        enemy = new Enemy();
                                    }
                                    delete bullet;
                                    firstShoot=true;
                                    bulletShow=false;
                                    break;

                                }
                                }
                                break;
                            case SDLK_ESCAPE:
                                {
                                std::ofstream pauseData("pause.bin", std::ios::out | std::ios::binary);
                                if (pauseData.is_open())
                                {
                                    pauseData.write(reinterpret_cast<const char*>(&x.xPlayer), sizeof(x.xPlayer));
                                    pauseData.write(reinterpret_cast<const char*>(&x.yPlayer), sizeof(x.yPlayer));
                                    pauseData.write(reinterpret_cast<const char*>(&totalKills), sizeof(totalKills));
                                    pauseData.write(reinterpret_cast<const char*>(&killCount), sizeof(killCount));
                                    pauseData.write(reinterpret_cast<const char*>(&arenaEnemyKillCount), sizeof(arenaEnemyKillCount));
                                    pauseData.write(reinterpret_cast<const char*>(&arenaCount), sizeof(arenaCount));
                                    pauseData.write(reinterpret_cast<const char*>(&level), sizeof(level));
                                    pauseData.close();
                                    pause();
                                }
                                break;
                            }
                            default:
                                gPlayer = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                                x.offScreen();
                                break;
                        }
                    }
                }
                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
			//render background
			SDL_BlitSurface( gBackground, NULL, gScreenSurface, NULL );


			//renders arenas if player is less than 100px away
            if(x.xPlayer<arena->xArena+400 && x.xPlayer>arena->xArena-100 && x.yPlayer<arena->yArena+300 && x.yPlayer>arena->yArena-10){
                showArena=true;
                battleBegin=true;
            }

            if(showArena){
                SDL_Rect destA;
                destA.x = arena->xArena;
                destA.y = arena->yArena;
                destA.w = 300;
                destA.h = 200;
                SDL_BlitScaled( gArena, NULL, gScreenSurface, &destA );
			}

			bool colAP=false;
			if(battleBegin){
                //render enemies in arena
                SDL_Rect destAE;
                destAE.x = arenaEnemy->xArenaEnemy;
                destAE.y = arenaEnemy->yArenaEnemy;
                destAE.w = 60;
                destAE.h = 60;
                SDL_BlitScaled( gArenaEnemy, NULL, gScreenSurface, &destAE );

                int A2=x.xPlayer;
                int B2=x.xPlayer+60;
                int C2=x.yPlayer;
                int D2=x.yPlayer+60;

                int A1=arenaEnemy->xArenaEnemy;
                int B1=arenaEnemy->xArenaEnemy+60;
                int C1=arenaEnemy->yArenaEnemy;
                int D1=arenaEnemy->yArenaEnemy+60;

                //if(x.xPlayer<arenaEnemy->xArenaEnemy+200 && x.xPlayer>arenaEnemy->xArenaEnemy-200 && x.yPlayer<arenaEnemy->yArenaEnemy+200 && x.yPlayer>arenaEnemy->yArenaEnemy-200){
                if(D1<=C2)
                    colAP=true;
                if(C1>=D2)
                    colAP=true;
                if(B1<=A2)
                    colAP=true;
                if(A1>=B2)
                    colAP=true;
                //}
                if(colAP ){ //!colEnemy
                    if(arenaEnemy->xArenaEnemy>x.xPlayer)
                        arenaEnemy->xArenaEnemy-=0.5;
                    else
                        arenaEnemy->xArenaEnemy+=0.5;
                    if(arenaEnemy->yArenaEnemy>x.yPlayer)
                        arenaEnemy->yArenaEnemy-=0.5;
                    else
                        arenaEnemy->yArenaEnemy+=0.5;
                }
            }

			//render bullet
			if(bulletShow){
                SDL_Rect destB;
                destB.x = bullet->xBullet;
                destB.y = bullet->yBullet;
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

            if(showBull){
                SDL_Rect destB;
                destB.x = bull->xBull;
                destB.y = bull->yBull;
                destB.w = 60;
                destB.h = 60;
                SDL_BlitScaled( gBull, NULL, gScreenSurface, &destB );

            }

            if(showBull){
                SDL_Rect destD;
                destD.x = door->xDoor;
                destD.y = door->yDoor;
                destD.w = 60;
                destD.h = 60;
                SDL_BlitScaled( gDoor, NULL, gScreenSurface, &destD );

            }
            bool colBP=false;
            if(showBull){
                int A22=x.xPlayer;
                int B22=x.xPlayer+60;
                int C22=x.yPlayer;
                int D22=x.yPlayer+60;

                int A11=bull->xBull;
                int B11=bull->xBull+60;
                int C11=bull->yBull;
                int D11=bull->yBull+60;

                if(x.xPlayer<bull->xBull+200 && x.xPlayer>bull->xBull-200 && x.yPlayer<bull->yBull+200 && x.yPlayer>bull->yBull-200){
                if(D11<=C22)
                    colBP=true;
                if(C11>=D22)
                    colBP=true;
                if(B11<=A22)
                    colBP=true;
                if(A11>=B22)
                    colBP=true;
                }

                if(bull->xBull+200 && x.xPlayer>bull->xBull-200 && x.yPlayer<bull->yBull+200 && x.yPlayer>bull->yBull-200 && colBP){
                        if(bull->xBull>x.xPlayer)
                            bull->xBull-=0.5;
                        else
                            bull->xBull+=0.5;
                        if(bull->yBull>x.yPlayer)
                            bull->yBull-=0.5;
                        else
                            bull->yBull+=0.5;
                        }
                        SDL_Rect destB;
                        destB.x = bull->xBull;
                        destB.y = bull->yBull;
                        destB.w = 60;
                        destB.h = 60;
                        SDL_BlitScaled( gBull, NULL, gScreenSurface, &destB );
                        if((door->xDoor+60 && bull->xBull>door->xDoor-60 && bull->yBull<door->yDoor+60 && bull->yBull>door->yDoor-60 ))
                        {
                            showBull=false;
                            delete bull;
                            delete door;
                        }
            }

            bool col=false;
            //render enemies

                SDL_Rect destE;
                destE.x = enemy->xEnemy;
                destE.y = enemy->yEnemy;
                destE.w = 60;
                destE.h = 60;
                SDL_BlitScaled( gEnemy, NULL, gScreenSurface, &destE );
                //chases player if less than 200px away

                //collisiion
                int A222=x.xPlayer;
                int B222=x.xPlayer+60;
                int C222=x.yPlayer;
                int D222=x.yPlayer+60;

                int A111=enemy->xEnemy;
                int B111=enemy->xEnemy+60;
                int C111=enemy->yEnemy;
                int D111=enemy->yEnemy+60;

                if(x.xPlayer<enemy->xEnemy+200 && x.xPlayer>enemy->xEnemy-200 && x.yPlayer<enemy->yEnemy+200 && x.yPlayer>enemy->yEnemy-200){
                if(D111<=C222)
                    col=true;
                if(C111>=D222)
                    col=true;
                if(B111<=A222)
                    col=true;
                if(A111>=B222)
                    col=true;


                if(enemy->xEnemy+200 && x.xPlayer>enemy->xEnemy-200 && x.yPlayer<enemy->yEnemy+200 && x.yPlayer>enemy->yEnemy-200 && col ){ //!colEnemy
                    if(enemy->xEnemy>x.xPlayer)
                        enemy->xEnemy-=0.5;
                    else
                        enemy->xEnemy+=0.5;
                    if(enemy->yEnemy>x.yPlayer)
                        enemy->yEnemy-=0.5;
                    else
                        enemy->yEnemy+=0.5;
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
		gWindow = SDL_CreateWindow( "Rescue Bull Ferdinand", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

	gMenuBackground = SDL_LoadBMP( "menu.bmp" );
	if( gMenuBackground == NULL )
	{
		cout<<"Unable to load image %s! SDL Error: \n"<< "menubg.bmp"<< SDL_GetError();
		success = false;
	}

	gPause = SDL_LoadBMP( "pause.bmp" );
	if( gPause == NULL )
	{
		cout<<"Unable to load image %s! SDL Error: \n"<< "pause.bmp"<< SDL_GetError();
		success = false;
	}

    gArena=SDL_LoadBMP("arena.bmp");

    gArenaEnemy=SDL_LoadBMP("arenaEnemy.bmp");

    gEnemy=SDL_LoadBMP("enemy.bmp");

    gBullet=SDL_LoadBMP("bullet.bmp");

    gBull=SDL_LoadBMP("bull.bmp");

    gDoor=SDL_LoadBMP("door.bmp");

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
	//Deallocate surface
	SDL_FreeSurface( gBackground );
	gBackground = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void Game::hidePauseScreen()
{
    SDL_FreeSurface( gPause );
	gPause = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems

}


