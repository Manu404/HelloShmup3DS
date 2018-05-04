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
    int frameSinceLastShot;
public:
    Enemy(SDL_Surface* buffer, Vector2* position, Vector2* sprite, int speed);
    void Animate();
};

class DefaultEnemy : public Enemy {
public:
    DefaultEnemy(SDL_Surface* buffer, Vector2* position);
};

class EnemyManager {
    std::list<Enemy*> enemies;
    SDL_Surface* buffer;
public:
    EnemyManager(SDL_Surface* buffer);
    ~EnemyManager();
    void Animate();
    void Display();
    void AddEnemy(int enemyType, Vector2* position, int behaviour);
};
#endif