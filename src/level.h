#ifndef LEVEL_H
#define LEVEL_H


#include "SDL/SDL.h"
#include "input.h"
#include "background.h"
#include "ship.h"
#include "bullet.h"
#include "enemy.h"
#include "gui.h"

class Level {
    SDL_Surface *backsurface;

    int is_level_running = 1, is_paused = 0, frame = 0;
    BulletManager *bulletManager;
    EnemyManager *enemyManager;
    GameData *data;
    LevelBackground *levelBackground;
    Ship *ship;

    InputMgmt *im;
    UserInterface *ui;
    Audio* audio;

    void RunGameOver();
    void Run();
    void AnimateLevel();
    void DisplayLevel();
    void DeleteLevelObjects();
    void CreateLevelObject();
    void GenerateEnemy();

public:
    Level(InputMgmt* im, UserInterface* ui, Audio* audio, SDL_Surface* backsurface);
    void Run(SDL_Surface* screen);
    void ResetLevel();
};
#endif