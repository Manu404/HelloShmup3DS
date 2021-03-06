#ifndef ENEMY_H
#define ENEMY_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "bullet.h"
#include "core.h"
#include <memory>

#define ENEMY_SPRITE "romfs:/enemy.png"

#define ENEMY_SPEED 7
#define ENEMY_DEFAULT_ENEMY_SPEED 5


class Enemy : public Sprite {
    int speed;
    int life;
public:
    int FrameSinceLastShot;
    int Agressivity;
    int Points;
    Enemy(SDL_Surface* buffer, Vector2* position, Vector2* sprite, int speed, int agressivity);
    void Animate();
    void ApplyDamage(int damage);
    int IsAlive();
};


class DefaultEnemy : public Enemy {
public:
    DefaultEnemy(SDL_Surface* buffer, Vector2* position);
};


class EnemyManager {
    SDL_Surface* buffer;
public:
    std::list<Enemy*> Enemies;
    EnemyManager(SDL_Surface* buffer);
    ~EnemyManager();
    void Animate();
    void Display();
    void AddEnemy(int enemyType, Vector2* position, int behaviour);
    void InitializeGraphics();
    void Reset();
};
#endif