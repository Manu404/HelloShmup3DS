#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "input.h"
#include "background.h"
#include "ship.h"
#include "bullet.h"
#include "enemy.h"
#include "gui.h"

class Game {
    int game_running = 1, frame = 0, is_init;
    SDL_Surface *screen, *backsurface;
    InputMgmt *im;
    Ship *ship;
    Background *background;
    BulletManager *bulletManager;
    EnemyManager *enemyManager;
    GameData *data;
    UserInterface *ui;

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