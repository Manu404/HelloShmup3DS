#ifndef Background_H
#define Background_H
#include "sprite.h"
#include "input.h"

class BackgroundLayer: public Sprite {
		int speed;
	public:
		BackgroundLayer(char*, int);
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