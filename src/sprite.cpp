#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"

Sprite::Sprite(char* path, int framePerRow, int width, int height, int x, int y) {
	currentRow = 0;
	currentFrame = 0;
	this->framePerRow = framePerRow;
	this->width = width;
	this->height = height;  
	this->image = IMG_Load(path);
	this->x=x;
	this->y=y;
	if(this->image == NULL)
		printf("Can't load image");
}

void Sprite::Display(SDL_Surface* buffer, int x, int y) {
	SDL_Rect srcrect = { currentFrame * width, currentRow * height, width, height };
	SDL_Rect dstrect = { x, y, width, height };
	SDL_BlitSurface(image, &srcrect, buffer, &dstrect);
}

void Sprite::Animate() {
	if(animate) {
		currentFrame += 1;
		if(currentFrame > framePerRow) currentFrame = 0;
	}
}

void Sprite::Display(SDL_Surface* buffer) {
	this->Display(buffer, this->x, this->y);
}

void Sprite::SetAnimation(int animation) {
	currentRow = animation;
}

void Sprite::StartAnimation() {
	animate = 1;
}

void Sprite::StopAnimation() {
	animate = 0;
}