#ifndef Bullet_H
#define Bullet_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "core.h"
#include <iostream>
#include <list>
#include "enemy.h"

#define BLUE_BULLET_SPRITE "romfs:/blue-bullet.png"
#define BLUE_BULLET_ANIMATION_PER_ROW 4
#define BLUE_BULLET_SPRITE_WIDTH 32
#define BLUE_BULLET_SPRITE_HEIGHT 32
#define BLUE_BULLET_SPEED 15
#define BLUE_BULLET_FRAME_PER_ANIMATION 3
#define BLUE_BULLET_SHOT_SPEED 3
#define BLUE_BULLET_FORCE 1

#define REDCROSS_BULLET_SPRITE "romfs:/red-cross-bullet.png"
#define REDCROSS_BULLET_ANIMATION_PER_ROW 2
#define REDCROSS_BULLET_SPRITE_WIDTH 32
#define REDCROSS_BULLET_SPRITE_HEIGHT 32
#define REDCROSS_BULLET_SPEED 10
#define REDCROSS_BULLET_FRAME_PER_ANIMATION 3
#define REDCROSS_BULLET_SHOT_SPEED 3
#define REDCROSS_BULLET_FORCE 1

#define EXPLOSION_BULLET_SPRITE "romfs:/explosion.png"
#define EXPLOSION_BULLET_ANIMATION_PER_ROW 9
#define EXPLOSION_BULLET_SPRITE_WIDTH 32
#define EXPLOSION_BULLET_SPRITE_HEIGHT 32
#define EXPLOSION_BULLET_SPEED 0
#define EXPLOSION_BULLET_FRAME_PER_ANIMATION 1
#define EXPLOSION_BULLET_SHOT_SPEED 3


class Bullet : public Sprite {
    float speed;
    Vector2* direction;
public:
    int Force;
    int HasHit = false;
    Bullet(char* path, int animationPerRow, int framePerAnimation, Vector2* position, Vector2* direction, Vector2* size, float speed, SDL_Surface* buffer, int repeat, int force);
    void Animate();
};

class BlueBullet : public Bullet {
public:
    BlueBullet(SDL_Surface* buffer, Vector2* position, Vector2* direction);
};

class RedCrossBullet : public Bullet {
public:
    RedCrossBullet(SDL_Surface* buffer, Vector2* position, Vector2* direction);
};

class ExplosionBullet : public Bullet {
public:
    ExplosionBullet(SDL_Surface* buffer, Vector2* position);
};

class BulletManager {
    std::list<Bullet*> bullets;
    std::list<Bullet*> enemyBullet;
    std::list<Bullet*> explosions;
    SDL_Surface* buffer;
public:
    BulletManager(SDL_Surface* buffer);
    ~BulletManager();
    void Animate();
    void Display();
    void AddBlueBullet(int x, int y);
    void AddBlueBullet(Vector2* position, Vector2* direction);
    void AddEnemyBullet(Vector2* position, Vector2* direction);
    void AddExplosion(Vector2* position);
    void InitializeGraphics();
    void HandleCollisionWithEnemy(EnemyManager* enemyManager, GameData* data);
};

#endif