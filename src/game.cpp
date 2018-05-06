#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
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
    this->DeleteLevelObjects();
    /*delete this->im;
    delete this->ui;
    delete this->data;*/

    romfsExit();

    SDL_FreeSurface(this->backsurface);
    SDL_FreeSurface(this->screen);
    SDL_Quit();
    TTF_Quit();
}

void Game::ResetLevel()
{
    this->DeleteLevelObjects();
    this->CreateLevelObject();
}

void Game::DeleteLevelObjects()
{
    delete this->levelBackground;
    delete this->bulletManager;
    delete this->enemyManager;
    delete this->ship;
}

void Game::CreateLevelObject() {
    this->ship = new Ship(this->backsurface);
    this->levelBackground = new LevelBackground(this->backsurface);
    this->bulletManager = new BulletManager(this->backsurface);
    this->enemyManager = new EnemyManager(this->backsurface);
}

void Game::Run() {
    if (!is_init) return;

    while (game_running == 1) {
        frame += 1;

        if (disabledInput > 0) {
            disabledInput -= 1;
        }

        im->HandleEvent();

        if (im->IsQuitRequested())
            game_running = 0;

        if(is_title) {
            RunTitle();
        }
        else if (data->GetLife() > 0) {
            RunLevel();
        } 
        else {
            RunGameOver();
        }

        SDL_BlitSurface(backsurface, NULL, screen, NULL);

        SDL_Flip(screen);
    }
    printf("exit");
}

void Game::RunLevel() {
    ship->HandleInput(im, bulletManager);

    if (disabledInput > 0) {
        return;
    }

    if(im->IsKeyStartPressed() && !is_paused) {
        is_paused = true;
        disabledInput = InputWaitFrame;
        return;
    }
    
    if (im->IsKeyStartPressed() && is_paused) {
        is_paused = false;
        disabledInput = InputWaitFrame;
        return;
    }

    if (is_paused) {
        ui->DisplayPause();
        return;
    }

    levelBackground->Animate();
    enemyManager->Animate();
    bulletManager->Animate();
    ship->Animate();

    bulletManager->HandleCollisionWithEnemy(enemyManager, data, ship);

    if (frame % 30 == 0) {
        Vector2* position = new Vector2(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 40));
        enemyManager->AddEnemy(1, position, 1);
        Vector2* adjustedPosition = new Vector2(ship->x - position->x, ship->y - position->y);
        bulletManager->AddEnemyBullet(position, adjustedPosition->Normalize());
    }

    levelBackground->DisplayBackground();
    enemyManager->Display();
    ship->Display();
    bulletManager->Display();
    levelBackground->DisplayOverlay();

    ui->Display(data);
}

void Game::RunTitle() {
    title_background->Animate();
    title_background->DisplayBackground();

    ui->DisplayTitle();

    title_background->DisplayOverlay();

    if (disabledInput) return;
    if (im->IsKeyStartPressed() || im->IsKeyAPressed()) {
        this->CreateLevelObject();
        this->data->Reset();
        is_title = false;
        disabledInput = InputWaitFrame;
    }
    else if (im->IsKeySelectPressed()) {
        game_running = 0;
    }
}

void Game::RunGameOver()
{
    ui->DisplayGameOver(data);
    if (im->IsKeyStartPressed()) {
        this->ResetLevel();
        data->Reset();
        disabledInput = InputWaitFrame;
    }
    else if(im->IsKeySelectPressed()) {
        is_title = true;
        disabledInput = InputWaitFrame;
        this->DeleteLevelObjects();
    }
}


void Game::Initialize() {
    this->is_init = true;
    this->InitRomFs();
    this->InitSDL();
    this->InitVideo();
    this->InitAudio();
    this->InitGameEngine();
    this->InitGraphics();
}

void Game::InitGameEngine() {
    this->im = new InputMgmt();
    this->ui = new UserInterface(this->backsurface);
    this->data = new GameData();
    this->title_background = new TitleBackground(this->backsurface);
    this->CreateLevelObject();
}

void Game::InitGraphics() {
    this->bulletManager->InitializeGraphics();
    this->enemyManager->InitializeGraphics();
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
    if (TTF_Init() < 0) {
        // Handle error...
    }
}

void Game::InitAudio() {
    Mix_Music *music = NULL;
    int flags = MIX_INIT_MP3;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
    }

    //Load the music
    music = Mix_LoadMUS("romfs:/Vampire.it");

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