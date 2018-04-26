#ifndef Ship_H
#define Ship_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define Ship_ANIMATION_UP 0
#define Ship_ANIMATION_FT 1
#define Ship_ANIMATION_DN 2

#define Ship_FRAME_PER_ANIMATION 0
#define Ship_SPRITE_WIDTH 32
#define Ship_SPRITE_HEIGHT 32

#define Ship_SPEED 7

class Ship: public Sprite {
		int speed;
	public:
		Ship(SDL_Surface* buffer);
		void HandleInput(InputManager*);
};

#endif