#ifndef TITLE_H
#define TITLE_H
#include <SDL/SDL.h>
#include "gui.h"
#include "Audio.h"
#include "input.h"
#include "background.h"

class Title {
    int frame, game_running;
    SDL_Surface* backsurface;

    UserInterface* ui;
    Audio* audio;
    InputMgmt *im;

    TitleBackground *title_background;

public:
    Title(SDL_Surface* backsurface, UserInterface* ui, Audio* audio, InputMgmt *im);
    void Run(SDL_Surface* backsurface);
};

#endif