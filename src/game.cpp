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
#include "enemy.h"
#include "game.h"

Game::Game() {

}

Game::~Game() {
    delete this->im;
    delete this->background;
    delete this->bulletManager;
    delete this->enemyManager;
    delete this->ship;

    romfsExit();

    SDL_FreeSurface(this->backsurface);
    SDL_FreeSurface(this->screen);
    SDL_Quit();
}

void Game::Run() {
    if (!is_init) return;

    while (game_running == 1) {
        frame += 1;

        im->HandleEvent();

        if (im->IsKeySelectPressed() || im->IsQuitRequested())
            game_running = 0;

        ship->HandleInput(im, bulletManager);

        if (frame % 30 == 0) {
            enemyManager->AddEnemy(1, new Vector2(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 40)), 1);
        }

        background->Animate();
        enemyManager->Animate();
        bulletManager->Animate();

        background->DisplayBackground();
        enemyManager->Display();
        ship->Display();
        bulletManager->Display();
        background->DisplayOverlay();

        SDL_BlitSurface(backsurface, NULL, screen, NULL);

        SDL_Flip(screen);
    }
}

void Game::Initialize() {
    this->is_init = true;
    this->InitRomFs();
    this->InitSDL();
    this->InitVideo();
    this->InitGraphics();
    this->InitAudio();
    this->InitGameEngine();
}

void Game::InitGameEngine() {
    this->im = new InputMgmt();
    this->ship = new Ship(this->backsurface);
    this->background = new Background(this->backsurface);
    this->bulletManager = new BulletManager(this->backsurface);
    this->enemyManager = new EnemyManager(this->backsurface);
}

void Game::InitGraphics() {

}

void Game::InitVideo() {
    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_HWSURFACE | SDL_TOPSCR | SDL_CONSOLEBOTTOM);

    SDL_Surface *surf = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT,
        screen->format->BitsPerPixel,
        screen->format->Rmask,
        screen->format->Gmask,
        screen->format->Bmask,
        screen->format->Amask);

    this->backsurface = SDL_ConvertSurface(surf, screen->format, SDL_HWSURFACE);

    SDL_FreeSurface(surf);
}

void Game::InitSDL() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
    SDL_ShowCursor(SDL_DISABLE);
}

void Game::InitAudio() {
    Mix_Music *music = NULL;
    int flags = MIX_INIT_MP3;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
    }

    //Load the music
    music = Mix_LoadMUS("romfs:/vampire.it");

    //If there was a problem loading the music
    if (music == NULL)
    {
        printf("Error loading music: %s\n", Mix_GetError());
    }

    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music, -1);
    }
}

void Game::InitRomFs() {
    Result rs = romfsInit();
    if (rs)
        printf("romfsInit: %08lx\n", rs);
    else {
        printf("romfs Initialization succeed.\n");
    }
}