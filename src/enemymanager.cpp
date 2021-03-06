#include "sprite.h"
#include "SDL/SDL.h"
#include "bullet.h"
#include "core.h"
#include "enemy.h"
#include "main.h"

EnemyManager::EnemyManager(SDL_Surface* buffer) {
    this->buffer = buffer;
}

EnemyManager::~EnemyManager() {
    std::list<Enemy*>::const_iterator iterator;
    for (iterator = Enemies.begin(); iterator != Enemies.end(); ++iterator) {
        delete (*iterator);
    }
}

void EnemyManager::Animate() {
    std::list<Enemy*>::const_iterator iterator;
    for (iterator = Enemies.begin(); iterator != Enemies.end(); ++iterator) {
        (*iterator)->Animate();
        if ((*iterator)->x > SCREEN_WIDTH || (*iterator)->y > SCREEN_HEIGHT || (*iterator)->x < (0 - (*iterator)->width) || (*iterator)->y < (0 - (*iterator)->height))
            delete (*iterator);
        if (!(*iterator)->IsAlive())
            delete (*iterator);
    }

    Enemies.remove_if([](Enemy* b) { return b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT || b->x < (0 - b->width) || b->y < (0 - b->height) || !b->IsAlive(); });
}

void EnemyManager::Display() {
    std::list<Enemy*>::const_iterator iterator;
    for (iterator = Enemies.begin(); iterator != Enemies.end(); ++iterator) {
        (*iterator)->Display();
    }
}

void EnemyManager::AddEnemy(int enemyType, Vector2* position, int behaviour) {
    switch (enemyType) {
    case 1: Enemies.push_back(new Enemy(this->buffer, position, new Vector2(rand() % 8, rand() % 4), (rand() % 10), (rand() % 30 + 30 ))); break;
    default: break;
    }
}

void EnemyManager::InitializeGraphics() {
    Enemy* e = new Enemy(this->buffer, new Vector2(0, 0), new Vector2(0, 0), 0, 0);
    delete e;
}

void EnemyManager::Reset() {
    std::list<Enemy*>::const_iterator iterator;
    for (iterator = Enemies.begin(); iterator != Enemies.end(); ++iterator) {
        delete (*iterator);
    }
    Enemies.clear();
}