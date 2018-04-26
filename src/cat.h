#ifndef Cat_H
#define Cat_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define CAT_ANIMATION_UP 3
#define CAT_ANIMATION_DN 0
#define CAT_ANIMATION_LT 1
#define CAT_ANIMATION_RT 2

#define CAT_FRAME_PER_ANIMATION 3
#define CAT_SPRITE_WIDTH 32
#define CAT_SPRITE_HEIGHT 32

#define CAT_SPEED 7

class Cat: public Sprite {
        int speed;
    public:
        Cat(SDL_Surface* buffer);
        void HandleInput(InputManager*);
};

#endif