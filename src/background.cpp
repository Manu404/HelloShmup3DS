#include "background.h"
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

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
    Sprite::Display(this->x, this->y);
    Sprite::Display(this->x + this->width, this->y);
}

Background::Background(SDL_Surface* buffer) {
    this->layers[0] = new BackgroundLayer("romfs:/bg/bg1.png", 1, 400, 250, buffer);
    this->layers[1] = new BackgroundLayer("romfs:/bg/bg2.png", 3, 400, 79, buffer);
    this->layers[2] = new BackgroundLayer("romfs:/bg/bg3.png", 4, 400, 88, buffer);
    this->layers[3] = new BackgroundLayer("romfs:/bg/bg4.png", 6, 400, 140, buffer);
    this->layers[4] = new BackgroundLayer("romfs:/bg/bg5.png", 8, 400, 16, buffer);
    this->layers[5] = new BackgroundLayer("romfs:/bg/bg6.png", 10, 400, 18, buffer);
}

void Background::Animate() {
    for(int i = 0; i <= 5; i++) {
        this->layers[i]->Animate();
    }
}

void Background::DisplayBackground() {
    for(int i = 0; i <= 4; i++) {
        this->layers[i]->Display();
    }
}

void Background::DisplayOverlay() {
    for(int i = 5; i <= 5; i++) {
        this->layers[i]->Display();
    }
}

Background::~Background() {
    for (int i = 0; i <= 5; i++) {
        delete this->layers[i];
    }
}


