#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "sprite.h"
#include "input.h"
#include "cat.h"
#include "background.h"
#include "ship.h"
#include "main.h"
#include "bullet.h"

int main(int argc, char **argv)
{
    int game_running = 1;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
    SDL_Surface *screen;
    SDL_ShowCursor(SDL_DISABLE);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_HWSURFACE | SDL_TOPSCR | SDL_CONSOLEBOTTOM);

    SDL_Surface* surf = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT,
        screen->format->BitsPerPixel,
        screen->format->Rmask,
        screen->format->Gmask,
        screen->format->Bmask,
        screen->format->Amask);

    SDL_Surface *backsurface = SDL_ConvertSurface(surf, screen->format, SDL_HWSURFACE);

    InitRomFs();

    //InitAudio();

    InputMgmt* im = new InputMgmt();
	
    Ship* ship = new Ship(backsurface);
    Background* background = new Background(backsurface);
    BulletManager* bulletManager = new BulletManager(backsurface);
	
    while(game_running == 1) {
        im->HandleEvent();

        if (im->IsKeySelectPressed() || im->IsQuitRequested())
            game_running = 0;

        ship->HandleInput(im, bulletManager);

        background->Animate();
        background->DisplayBackground();
        ship->Display();

        bulletManager->Animate();
        bulletManager->Display();
		
        background->DisplayOverlay();	
		
        SDL_BlitSurface(backsurface, NULL, screen, NULL);
		
        SDL_Flip(screen);
    }

    delete im;
    delete background;
    delete bulletManager;
    delete ship;
    
    romfsExit();
    SDL_FreeSurface(backsurface);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(surf);
    SDL_Quit();
    return 0;
}


void InitAudio() {
    Mix_Music *music = NULL;
    int flags = MIX_INIT_MP3;
	
    if( Mix_OpenAudio( 22050, AUDIO_S16, 2, 1024) < 0) 
    {
    	printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
    }

    //Load the music
    music = Mix_LoadMUS( "romfs:/bg.mp3" );
    
    //If there was a problem loading the music
    if( music == NULL )
    {
        printf("Error loading music: %s\n", Mix_GetError());
    }

    if( Mix_PlayingMusic() == 0 )
    {
         Mix_PlayMusic(music, -1);            
    }
}

void InitRomFs() {
    Result rs = romfsInit();
    if (rs)
        printf("romfsInit: %08lx\n", rs);
    else {
        printf("romfs Initialization succeed.\n");
    }
}

