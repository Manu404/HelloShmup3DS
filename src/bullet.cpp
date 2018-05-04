#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include "input.h"
#include "bullet.h"
#include "core.h"
#include "main.h"

Bullet::Bullet(char* path, int animationPerRow, int framePerAnimation, Vector2* position, Vector2* direction, Vector2* size, int speed, SDL_Surface* buffer)
    : Sprite(path, animationPerRow, framePerAnimation, size->x, size->y, position->x, position->y, buffer, 0, 0) {
    this->speed = speed;
    this->direction = direction;
}

void Bullet::Animate() {
    this->x += this->direction->x * this->speed;
    this->y += this->direction->y * this->speed;
    Sprite::Animate();
}

BlueBullet::BlueBullet(SDL_Surface* buffer, Vector2* position, Vector2* direction) 
    : Bullet(BLUE_BULLET_SPRITE, BLUE_BULLET_ANIMATION_PER_ROW, BLUE_BULLET_FRAME_PER_ANIMATION, position, direction, new Vector2(BLUE_BULLET_SPRITE_WIDTH, BLUE_BULLET_SPRITE_HEIGHT), BLUE_BULLET_SPEED, buffer) {
}


