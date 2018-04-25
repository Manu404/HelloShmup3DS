#include "background.h"
#include "sprite.h"
#include "input.h"

BackgroundLayer::BackgroundLayer(char* bgPath, int scrollingSpeed, int width, int height) : Sprite(bgPath, 0, width, height, 0, 0) {
	this->speed = scrollingSpeed;
}

void BackgroundLayer::Animate() {
	this->x -= this->speed;
	if(this->x < (-(this->width)))
		this->x = 0;
	
	this->y = 240 - this->height;
}

void BackgroundLayer::Display(SDL_Surface* buffer) {
	Sprite::Display(buffer, this->x, this->y);
	Sprite::Display(buffer, this->x + this->width, this->y);
}

Background::Background() {
	this->layers[0] = new BackgroundLayer("romfs:/bg/bg1.png", 1, 400, 250);
	this->layers[1] = new BackgroundLayer("romfs:/bg/bg2.png", 3, 400, 79);
	this->layers[2] = new BackgroundLayer("romfs:/bg/bg3.png", 4, 400, 88);
	this->layers[3] = new BackgroundLayer("romfs:/bg/bg4.png", 6, 400, 140);
	this->layers[4] = new BackgroundLayer("romfs:/bg/bg5.png", 8, 400, 16);
	this->layers[5] = new BackgroundLayer("romfs:/bg/bg6.png", 10, 400, 18);
}

void Background::Animate() {
	for(int i = 0; i <= 5; i++) {
		this->layers[i]->Animate();
	}
}

void Background::Display(SDL_Surface* buffer) {
	for(int i = 0; i <= 5; i++) {
		if(i%2==0)
		this->layers[i]->Display(buffer);
	}
}

