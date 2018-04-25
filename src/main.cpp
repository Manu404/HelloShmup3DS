#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "sprite.h"
#include "input.h"
#include "cat.h"
#include "background.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
    SDL_Surface *screen;
    Mix_Music *music = NULL;
    SDL_ShowCursor(SDL_DISABLE);
    int flags = MIX_INIT_MP3;
    int result = 0;

    screen = SDL_SetVideoMode(400, 240, 16, SDL_SWSURFACE | SDL_TOPSCR | SDL_CONSOLEBOTTOM);

    Result rs = romfsInit();
    if (rs)
        printf("romfsInit: %08lx\n", rs);
    else {
        printf("romfs Initialization succeed.\n");
    }

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

    Cat* cat = new Cat();
	Background* background = new Background();
	InputManager* inputManager = new InputManager();
	
	SDL_Surface* surf = SDL_CreateRGBSurface(SDL_SWSURFACE, 400, 240, 
		screen->format->BitsPerPixel,
		screen->format->Rmask, 
		screen->format->Gmask, 
		screen->format->Bmask, 
		screen->format->Amask);
	
	SDL_Surface *backsurface = SDL_ConvertSurface(surf, screen->format, SDL_SWSURFACE);

    while(true) {
		inputManager->HandleEvent();
		cat->HandleInput(inputManager);
		cat->Animate();
		
		background->Animate();
		
		SDL_FillRect(backsurface, NULL, 0);
		background->Display(backsurface);
		cat->Display(backsurface);		
		
		SDL_BlitSurface(backsurface, NULL, screen, NULL);
		
		SDL_Flip(screen);
    }
    SDL_Quit();
  
    return 0;
}



