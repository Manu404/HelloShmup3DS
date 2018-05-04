#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "bullet.h"
#include "core.h"
#include "enemy.h"
#include "main.h"

EnemyManager::EnemyManager(SDL_Surface* buffer) {
    this->buffer = buffer;
}

EnemyManager::~EnemyManager() {
    std::list<Enemy*>::const_iterator iterator;
    for (iterator = enemies.begin(); iterator != enemies.end(); ++iterator) {
        delete (*iterator);
    }
}

void EnemyManager::Animate() {
    std::list<Enemy*>::const_iterator iterator;
    for (iterator = enemies.begin(); iterator != enemies.end(); ++iterator) {
        (*iterator)->Animate();
        if ((*iterator)->x > SCREEN_WIDTH || (*iterator)->y > SCREEN_HEIGHT)
            delete (*iterator);
    }

    enemies.remove_if([](Enemy* b) { return b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT; });
}

void EnemyManager::Display() {
    std::list<Enemy*>::const_iterator iterator;
    for (iterator = enemies.begin(); iterator != enemies.end(); ++iterator) {
        (*iterator)->Display();
    }
}

void EnemyManager::AddEnemy(int enemyType, Vector2* position, int behaviour) {
    switch (enemyType) {
        case 1: enemies.push_back(new Enemy(this->buffer, position, new Vector2(rand() % 8, rand() % 8), (rand() % 10) + 5)); break;
        default: break;
    }
}

Enemy::Enemy(SDL_Surface* buffer, Vector2* position, Vector2* sprite, int speed) : Sprite(ENEMY_SPRITE, (new Vector2(32, 32)), position, sprite, buffer) {
    this->speed = speed;
}

void Enemy::Animate() {
    Sprite::Animate();
    this->x -= speed;
}

DefaultEnemy::DefaultEnemy(SDL_Surface* buffer, Vector2* position) : Enemy(buffer, position, (new Vector2(0, 4)), ENEMY_DEFAULT_ENEMY_SPEED) {

}