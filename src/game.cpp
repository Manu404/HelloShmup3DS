#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "input.h"
#include "background.h"
#include "main.h"
#include "game.h"
#include <SDL/SDL_audio.h>

Game::Game() {

}

Game::~Game() {
    //this->DeleteLevelObjects();
    delete this->im;
    delete this->ui;
    delete this->audio;
    delete this->level;

    romfsExit();

    SDL_FreeSurface(this->backsurface);
    SDL_FreeSurface(this->screen);
    SDL_Quit();
    TTF_Quit();
}

void Game::Run() {
    if (!is_init) return;

    while (game_running == 1) {

        if (im->IsQuitRequested())
            game_running = false;

        if(is_title) {
            RunTitle();
        }
        else {
            level->Run(screen);
            is_title = true;
        } 
    }
    printf("exit");
}

void Game::RunLevel() {

}

void Game::RunTitle() {
    frame += 1;

    if (im->Disabled > 0) {
        im->Disabled -= 1;
    }
    
    im->HandleEvent();
    
    //audio->PlayTitleMusic();

    title_background->Animate();
    title_background->DisplayBackground();

    ui->DisplayTitle();

    title_background->DisplayOverlay();

    if (im->Disabled) return;
    if (im->IsKeyStartPressed() || im->IsKeyAPressed()) {
        this->level->ResetLevel();
        is_title = false;
        im->Disabled = InputWaitFrame;
    }
    else if (im->IsKeySelectPressed()) {
        game_running = 0;
    }

    SDL_BlitSurface(backsurface, NULL, screen, NULL);

    SDL_Flip(screen);
}

void Game::Initialize() {
    this->is_init = true;
    this->InitRomFs();
    this->InitSDL();
    this->InitVideo();
    this->InitAudio();
    this->InitGameEngine();
}

void Game::InitGameEngine() {
    this->im = new InputMgmt();
    this->ui = new UserInterface(this->backsurface);
    this->title_background = new TitleBackground(this->backsurface);
    //this->audio = new Audio();
    this->level = new Level(this->im, this->ui, this->audio, this->backsurface);
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
        printf("Error initializing SDL_TTF");
    }
}

void LoadTestAudioFiles()
{
    Mix_Chunk *sample;
    sample = Mix_LoadWAV("romfs:/sfx.ogg");
    if (!sample) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
    else {
        printf("LoadWAv OK \n");
    }

    Mix_Music* music = Mix_LoadMUS("romfs:/music.ogg");
    if (music == NULL) {
        printf("Error loading music: %s\n", Mix_GetError());
    }

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1);
    }
}

void Game::InitAudio() {
    int code = Mix_Init(MIX_INIT_OGG);
    std::cout << "OGG libraries loaded: " << code << std::endl;

    if (Mix_OpenAudio(22050, AUDIO_U16, 2, 1024) < 0) {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
    }
    else {
        printf("SDL_mixer Initialization succeed.\n");
    }

    //LoadTestAudioFiles();
}

void Game::InitRomFs() {
    Result rs = romfsInit();
    if (rs)
        printf("romfsInit: %08lx\n", rs);
    else {
        printf("romfs Initialization succeed.\n");
    }
}