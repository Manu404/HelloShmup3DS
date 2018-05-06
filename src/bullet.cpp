#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include "input.h"
#include "bullet.h"
#include "core.h"
#include "main.h"

Bullet::Bullet(char* path, int animationPerRow, int framePerAnimation, Vector2* position, Vector2* direction, Vector2* size, float speed, SDL_Surface* buffer, int repeat, int force)
    : Sprite(path, animationPerRow, framePerAnimation, size->x, size->y, position->x, position->y, buffer, 0, 0, 0, repeat) {
    this->speed = speed;
    this->direction = direction;
    this->Force = force;
}

void Bullet::Animate() {
    this->x += this->direction->x * this->speed;
    this->y += this->direction->y * this->speed;
    //printf("%.2f %2.f\n", this->x, this->direction->x);
    Sprite::Animate();
}

BlueBullet::BlueBullet(SDL_Surface* buffer, Vector2* position, Vector2* direction) 
    : Bullet(BLUE_BULLET_SPRITE, BLUE_BULLET_ANIMATION_PER_ROW, BLUE_BULLET_FRAME_PER_ANIMATION, position, direction, new Vector2(BLUE_BULLET_SPRITE_WIDTH, BLUE_BULLET_SPRITE_HEIGHT), BLUE_BULLET_SPEED, buffer, 1, BLUE_BULLET_FORCE) {
}

RedCrossBullet::RedCrossBullet(SDL_Surface* buffer, Vector2* position, Vector2* direction)
    : Bullet(REDCROSS_BULLET_SPRITE, REDCROSS_BULLET_ANIMATION_PER_ROW, REDCROSS_BULLET_FRAME_PER_ANIMATION, position, direction, new Vector2(REDCROSS_BULLET_SPRITE_WIDTH, REDCROSS_BULLET_SPRITE_HEIGHT), REDCROSS_BULLET_SPEED, buffer, 1, REDCROSS_BULLET_FORCE) {
}

ExplosionBullet::ExplosionBullet(SDL_Surface* buffer, Vector2* position)
    : Bullet(EXPLOSION_BULLET_SPRITE, EXPLOSION_BULLET_ANIMATION_PER_ROW, EXPLOSION_BULLET_FRAME_PER_ANIMATION, position, new Vector2(0, 0), new Vector2(EXPLOSION_BULLET_SPRITE_WIDTH, EXPLOSION_BULLET_SPRITE_HEIGHT), EXPLOSION_BULLET_SPEED, buffer, 0, 0) {
    //this->SetAnimation(rand() % 25);
}

