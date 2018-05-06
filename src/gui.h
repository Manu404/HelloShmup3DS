#ifndef GUI_H
#define GUI_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "core.h"

class UserInterface {
    TTF_Font* mainFont15;

    SDL_Surface* buffer, *scoreMessage, *lifeMessage, *gameOverMessage, *pressStartMessage;

    void LoadFonts();
    void InitializeStaticSurface();
public:
    UserInterface(SDL_Surface* buffer);
    ~UserInterface();
    void Display(GameData* data);
    void DisplayGameOver(GameData* data);
    void DisplayText(const char * text, SDL_Rect* position);
};

#endif