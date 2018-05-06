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
    /*this->layers[0] = new BackgroundLayer("romfs:/bg/bg1.png", 1, 400, 250, buffer);
    this->layers[1] = new BackgroundLayer("romfs:/bg/bg2.png", 3, 400, 79, buffer);
    this->layers[2] = new BackgroundLayer("romfs:/bg/bg3.png", 4, 400, 88, buffer);
    this->layers[3] = new BackgroundLayer("romfs:/bg/bg4.png", 6, 400, 140, buffer);
    this->layers[4] = new BackgroundLayer("romfs:/bg/bg5.png", 8, 400, 16, buffer);
    this->layers[5] = new BackgroundLayer("romfs:/bg/bg6.png", 10, 400, 18, buffer);*/


    this->layers.push_back(new BackgroundLayer("romfs:/bg/stars/bg1.png", 1, 400, 240, buffer));
    this->layers.push_back(new BackgroundLayer("romfs:/bg/stars/sb1.png", 3, 400, 240, buffer));
    this->layers.push_back(new BackgroundLayer("romfs:/bg/stars/sb2.png", 6, 400, 240, buffer));
    //this->layers.push_back(new BackgroundLayer("romfs:/bg/stars/sm1.png", 8, 400, 240, buffer));
    this->layers.push_back(new BackgroundLayer("romfs:/bg/stars/sm2.png", 8, 400, 240, buffer));
}

void Background::Animate() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = layers.begin(); iterator != layers.end(); ++iterator) {
        (*iterator)->Animate();
    }    
    for (iterator = overlay.begin(); iterator != overlay.end(); ++iterator) {
        (*iterator)->Animate();
    }
}

void Background::DisplayBackground() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = layers.begin(); iterator != layers.end(); ++iterator) {
        (*iterator)->Display();
    }
}

void Background::DisplayOverlay() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = overlay.begin(); iterator != overlay.end(); ++iterator) {
        (*iterator)->Display();
    }
}

Background::~Background() {
    std::list<BackgroundLayer*>::const_iterator iterator;
    for (iterator = layers.begin(); iterator != layers.end(); ++iterator) {
        delete (*iterator);
    }
    for (iterator = overlay.begin(); iterator != overlay.end(); ++iterator) {
        delete (*iterator);
    }
}


