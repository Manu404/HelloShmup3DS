#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "bullet.h"
#include "core.h"
#include "enemy.h"
#include "main.h"


Enemy::Enemy(SDL_Surface* buffer, Vector2* position, Vector2* sprite, int speed, int agressivity) : Sprite(ENEMY_SPRITE, (new Vector2(32, 32)), position, sprite, buffer) {
    this->speed = speed;
    this->life = rand() % 5;
    this->Points = rand() % 100;
    this->Agressivity = agressivity;
    this->FrameSinceLastShot = 0;
}

void Enemy::Animate() {
    Sprite::Animate();
    this->x -= speed;
}

void Enemy::ApplyDamage(int damage) {
    this->life -= damage;
}

int Enemy::IsAlive() {
    return this->life > 0;
}


DefaultEnemy::DefaultEnemy(SDL_Surface* buffer, Vector2* position) : Enemy(buffer, position, (new Vector2(0, 4)), ENEMY_DEFAULT_ENEMY_SPEED, 30) {

}