#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "input.h"
#include "background.h"
#include "gui.h"
#include "Audio.h"
#include "level.h"

#define InputWaitFrame 10

class Game {
    int frame = 0, is_init, is_title = 1, game_running = 1;
    SDL_Surface *screen, *backsurface;
    InputMgmt *im;
    TitleBackground *title_background;
    Level* level;
    UserInterface *ui;
    Audio* audio;

    void InitRomFs();
    void InitAudio();
    void InitSDL();
    void InitVideo();
    void InitGameEngine();
public:
    Game();
    ~Game();
    void Initialize();
    void Run();

    void RunLevel();
    void RunTitle();
};

#endif