#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"

Sprite::Sprite(char* path, int framePerRow, int width, int height, int x, int y, SDL_Surface* buffer) {
	currentRow = 0;
	currentFrame = 0;
	this->framePerRow = framePerRow;
	this->width = width;
	this->height = height;  
	this->buffer = buffer;
	this->image = this->LoadSurface(path);
	this->x=x;
	this->y=y;
	if(this->image == NULL)
		printf("Can't load image");
}

SDL_Surface* Sprite::LoadSurface( char* path )
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path);
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
	}
	else
	{
		optimizedSurface = SDL_DisplayFormatAlpha( loadedSurface );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

void Sprite::Display(int x, int y) {
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

void Sprite::Display() {
	this->Display(this->x, this->y);
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