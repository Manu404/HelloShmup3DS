#include "background.h"
#include "sprite.h"
#include "input.h"

BackgroundLayer::BackgroundLayer(char* bgPath, int scrollingSpeed) : Sprite(bgPath, 0, BG_WIDTH, BG_HEIGHT, 0, 0) {
	this->speed = scrollingSpeed;
}

void BackgroundLayer::Animate() {
	this->x -= this->speed;
	if(this->x < (-(this->width)))
		this->x = 0;
}

void BackgroundLayer::Display(SDL_Surface* buffer) {
	Sprite::Display(buffer, this->x, this->y);
	Sprite::Display(buffer, this->x + this->width, this->y);
}

Background::Background() {
	this->layers[0] = new BackgroundLayer("romfs:/bg/bg1.png", 1);
	this->layers[1] = new BackgroundLayer("romfs:/bg/bg2.png", 3);
	this->layers[2] = new BackgroundLayer("romfs:/bg/bg3.png", 4);
	this->layers[3] = new BackgroundLayer("romfs:/bg/bg4.png", 6);
	this->layers[4] = new BackgroundLayer("romfs:/bg/bg5.png", 8);
	this->layers[5] = new BackgroundLayer("romfs:/bg/bg6.png", 10);
}

void Background::Animate() {
	for(int i = 0; i <= 5; i++) {
		this->layers[i]->Animate();
	}
}

void Background::Display(SDL_Surface* buffer) {
	for(int i = 0; i <= 5; i++) {
		this->layers[i]->Display(buffer);
	}
}

