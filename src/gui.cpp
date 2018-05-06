#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "gui.h"
#include "core.h"
#include <string>
#include "main.h"

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
    SDL_Surface* lifeSurface = TTF_RenderText_Solid(mainFont15, std::to_string(data->GetLife()).c_str(), { 255, 255, 255 });

    SDL_Rect scoreRect = { 70, 10, 0, 0 };
    SDL_Rect scoreMessageRect = { 10, 10, 0, 0 };
    SDL_Rect lifeRect = { 370, 10, 0, 0 };
    SDL_Rect lifeMessageRect = { 330, 10, 0, 0 };

    SDL_BlitSurface(scoreMessage, NULL, buffer, &scoreMessageRect);
    SDL_BlitSurface(scoreSurface, NULL, buffer, &scoreRect);
    SDL_BlitSurface(lifeMessage, NULL, buffer, &lifeMessageRect);
    SDL_BlitSurface(lifeSurface, NULL, buffer, &lifeRect);
}

void UserInterface::DisplayGameOver(GameData* data) {
    SDL_Rect gameOverMessageRect = { (SCREEN_WIDTH / 2) - (gameOverMessage->w / 2), 75, 0, 0 };
    SDL_BlitSurface(gameOverMessage, NULL, buffer, &gameOverMessageRect);
    SDL_Rect pressStartMessageRect = { (SCREEN_WIDTH / 2) - (pressStartMessage->w / 2), 125, 0, 0 };
    SDL_BlitSurface(pressStartMessage, NULL, buffer, &pressStartMessageRect);
    SDL_Rect pressSelectMessageRect = { (SCREEN_WIDTH / 2) - (pressSelectMessage->w / 2), 140, 0, 0 };
    SDL_BlitSurface(pressSelectMessage, NULL, buffer, &pressSelectMessageRect);
}

void UserInterface::DisplayTitle() {
    SDL_Rect pressStartMessageRect = { (SCREEN_WIDTH / 2) - (pressStartTitleMessage->w / 2), 200, 0, 0 };
    SDL_BlitSurface(pressStartTitleMessage, NULL, buffer, &pressStartMessageRect);
}


void UserInterface::LoadFonts()
{
    mainFont15 = TTF_OpenFont("romfs:/silkscreen/slkscr.ttf", 15);
    titleFont10 = TTF_OpenFont("romfs:/bionic-kid/bionickidsimple.ttf", 10);
}

void UserInterface::InitializeStaticSurface()
{
    scoreMessage = TTF_RenderText_Solid(mainFont15, "Score", { 255, 255, 255 });
    lifeMessage = TTF_RenderText_Solid(mainFont15, "Life", { 255, 255, 255 });
    gameOverMessage = TTF_RenderText_Solid(mainFont15, "Game Over", { 255, 255, 255 });
    pressStartMessage = TTF_RenderText_Solid(mainFont15, "Press Start For New Game", { 255, 255, 255 });
    pressSelectMessage = TTF_RenderText_Solid(mainFont15, "Press Select For Home", { 255, 255, 255 });
    pressStartTitleMessage = TTF_RenderText_Solid(titleFont10, "Press Start", { 255, 255, 255 });
}

void UserInterface::DisplayText(const char* text, SDL_Rect* position)
{
    SDL_Surface* lifeSurface = TTF_RenderText_Solid(mainFont15, text, { 255, 255, 255 });
    SDL_BlitSurface(lifeSurface, NULL, buffer, position);
}



