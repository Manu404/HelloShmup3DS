#ifndef Bullet_H
#define Bullet_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "core.h"
#include <iostream>
#include <list>

#define BLUE_BULLET_SPRITE "romfs:/blue-bullet.png"
#define BLUE_BULLET_ANIMATION_PER_ROW 3
#define BLUE_BULLET_SPRITE_WIDTH 32
#define BLUE_BULLET_SPRITE_HEIGHT 32
#define BLUE_BULLET_SPEED 15
#define BLUE_BULLET_FRAME_PER_ANIMATION 3
#define BLUE_BULLET_SHOT_SPEED 3

class Bullet : public Sprite {
    int speed;
    Vector2* direction;
public:
    Bullet(char* path, int animationPerRow, int framePerAnimation, Vector2* position, Vector2* direction, Vector2* size, int speed, SDL_Surface* buffer);
    void Animate();
};

class BlueBullet : public Bullet {
public:
    BlueBullet(SDL_Surface* buffer, Vector2* position, Vector2* direction);
};

class BulletManager {
    std::list<Bullet*> bullets;
    SDL_Surface* buffer;
public:
    BulletManager(SDL_Surface* buffer);
    ~BulletManager();
    void Animate();
    void Display();
    void AddBlueBullet(int x, int y);
};

#endif