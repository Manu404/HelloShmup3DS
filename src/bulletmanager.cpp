#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "core.h"
#include <iostream>
#include <list>
#include "bullet.h"
#include "main.h"

BulletManager::BulletManager(SDL_Surface* buffer) {
    this->buffer = buffer;
}

BulletManager::~BulletManager() {
    std::list<Bullet*>::const_iterator iterator;
    for (iterator = bullets.begin(); iterator != bullets.end(); ++iterator) {
        delete (*iterator);
    }
}

void BulletManager::Animate() {
    std::list<Bullet*>::const_iterator iterator;
    for (iterator = bullets.begin(); iterator != bullets.end(); ++iterator) {
        (*iterator)->Animate();
        if ((*iterator)->x > SCREEN_WIDTH || (*iterator)->y > SCREEN_HEIGHT)
            delete (*iterator);
    }
 
    bullets.remove_if([](Bullet* b) { return b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT; });
}

void BulletManager::Display() {
    std::list<Bullet*>::const_iterator iterator;
    for (iterator = bullets.begin(); iterator != bullets.end(); ++iterator) {
        (*iterator)->Display();
    }
}

void BulletManager::AddBlueBullet(int x, int y) {
    bullets.push_back(new BlueBullet(buffer, new Vector2(x, y), new Vector2(1, 0)));
}