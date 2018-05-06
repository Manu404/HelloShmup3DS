#include "background.h"
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "main.h"

BackgroundLayer::BackgroundLayer(char* bgPath, int scrollingSpeed, int width, int height, SDL_Surface* buffer) : Sprite(bgPath, 0, width, height, 0, 0, buffer) {
    this->speed = scrollingSpeed;
}

void BackgroundLayer::Animate() {
    this->x -= this->speed;
    if(this->x < (-(this->width)))
        this->x = 0;
    this->y = 240 - this->height;
}

void BackgroundLayer::Display() {
    Sprite::Display(new Vector2(this->x, this->y));
    Sprite::Display(new Vector2(this->x + this->width, this->y));
}

Background::Background(SDL_Surface* buffer) {
}

void Background::Animate() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = Layers.begin(); iterator != Layers.end(); ++iterator) {
        (*iterator)->Animate();
    }    
    for (iterator = Overlay.begin(); iterator != Overlay.end(); ++iterator) {
        (*iterator)->Animate();
    }
}

void Background::DisplayBackground() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = Layers.begin(); iterator != Layers.end(); ++iterator) {
        (*iterator)->Display();
    }
}

void Background::DisplayOverlay() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = Overlay.begin(); iterator != Overlay.end(); ++iterator) {
        (*iterator)->Display();
    }
}

Background::~Background() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = Layers.begin(); iterator != Layers.end(); ++iterator) {
        delete (*iterator);
    }
    for (iterator = Overlay.begin(); iterator != Overlay.end(); ++iterator) {
        delete (*iterator);
    }
}

LevelBackground::LevelBackground(SDL_Surface* buffer) : Background(buffer)
{
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/bg1.png", 1, 400, 240, buffer));
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sb1.png", 3, 400, 240, buffer));
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sb2.png", 6, 400, 240, buffer));
    //this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sm1.png", 8, 400, 240, buffer));
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sm2.png", 8, 400, 240, buffer));
}

TitleBackground::TitleBackground(SDL_Surface* buffer) : Background(buffer)
{
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/bg2.png", 1, 400, 240, buffer));
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sb1.png", 3, 400, 240, buffer));
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sb2.png", 6, 400, 240, buffer));
    //this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sm1.png", 8, 400, 240, buffer));
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/sm2.png", 8, 400, 240, buffer));
    this->Layers.push_back(new BackgroundLayer("romfs:/bg/stars/title.png", 5, 400, 240, buffer));
}



