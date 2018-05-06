#ifndef Ship_H
#define Ship_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "bullet.h"

#define SHIP_ANIMATION_UP 0
#define SHIP_ANIMATION_FT 1
#define SHIP_ANIMATION_DN 2

#define SHIP_SPRITE "romfs:/ship2.png"
#define SHIP_ANIMATION_PER_ROW 3
#define SHIP_SPRITE_WIDTH 32
#define SHIP_SPRITE_HEIGHT 32

#define SHIP_SPEED 7

class Ship: public Sprite {
        int speed;
        int frameSinceLastShot;
        void HandleShipMovement(InputMgmt*);
        void HandleFire(InputMgmt*, BulletManager*);
    public:
        Ship(SDL_Surface* buffer);
        void HandleInput(InputMgmt*, BulletManager*);
};

#endif