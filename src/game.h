#ifndef GAME_H
#define GAME_H

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

class Game {
    int game_running = 1, frame = 0, is_init;
    SDL_Surface *screen, *backsurface;
    InputMgmt *im;
    Ship *ship;
    Background *background;
    BulletManager *bulletManager;
    EnemyManager *enemyManager;

    void InitRomFs();
    void InitAudio();
    void InitSDL();
    void InitVideo();
    void InitGraphics();
    void InitGameEngine();
public:
    Game();
    ~Game();
    void Initialize();
    void Run();
};

#endif