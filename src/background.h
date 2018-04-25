#ifndef Background_H
#define Background_H
#include "sprite.h"
#include "input.h"

#define BG_WIDTH 512
#define BG_HEIGHT 256

class BackgroundLayer: public Sprite {
		int speed;
	public:
		BackgroundLayer(char*, int, int, int);
		void Animate();
		void Display(SDL_Surface*);
};

class Background {
		BackgroundLayer* layers[6];
	public:
		Background();
		void Animate();
		void Display(SDL_Surface*);
};

#endif