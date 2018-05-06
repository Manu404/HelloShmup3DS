#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "gui.h"
#include "core.h"
#include <string>

UserInterface::UserInterface(SDL_Surface* buffer) {
    this->buffer = buffer;
    LoadFonts();
    InitializeStaticSurface();
}

UserInterface::~UserInterface() {
    
}

void UserInterface::Display(GameData* data)
{
    char str[7];
    snprintf(str, 7, "%06d", data->GetPoints());

    SDL_Surface* scoreSurface = TTF_RenderText_Solid(mainFont15, str, { 255, 255, 255 });
    SDL_Rect scoreRect = { 70, 10, 0, 0 };
    SDL_Rect scoreMessageRect = { 10, 10, 0, 0 };

    SDL_BlitSurface(scoreMessage, NULL, buffer, &scoreMessageRect);
    SDL_BlitSurface(scoreSurface, NULL , buffer, &scoreRect);
}

void UserInterface::LoadFonts()
{
    mainFont15 = TTF_OpenFont("romfs:/silkscreen/slkscr.ttf", 15);
}

void UserInterface::InitializeStaticSurface()
{
    scoreMessage = TTF_RenderText_Solid(mainFont15, "Score", { 255, 255, 255 });
}


