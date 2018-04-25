#ifndef Sprite_H

#define Sprite_H

#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Sprite {
	SDL_Surface *image;
	SDL_Rect viewPort;
	int currentRow;
	int currentFrame;
	int framePerRow;
	int animate;
	public:
		Sprite(char*,int,int,int,int,int);
		void Display(SDL_Surface*, int, int);
		void Display(SDL_Surface*);
		void Animate();
		void SetAnimation(int);
		void StartAnimation();
		void StopAnimation();
		
		int x;
		int y;
		int width;
		int height;
};
#endif