#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "core.h"
#include <iostream>
#include <list>
#include "bullet.h"
#include "main.h"
#include "ship.h"
#include "Audio.h"

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
    
    for (iterator = explosions.begin(); iterator != explosions.end(); ++iterator) {
        (*iterator)->Animate();
        if ((*iterator)->EndReached)
            delete (*iterator);
    }

    for (iterator = enemyBullet.begin(); iterator != enemyBullet.end(); ++iterator) {
        (*iterator)->Animate();
        if ((*iterator)->EndReached)
            delete (*iterator);
    }
 
    bullets.remove_if([](Bullet* b) { return b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT || b->x < 0 || b->y < 0; });
    enemyBullet.remove_if([](Bullet* b) { return b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT || b->x < 0 || b->y < 0; });
    explosions.remove_if([](Bullet* b) { return b->EndReached; });
}

void BulletManager::Display() {
    std::list<Bullet*>::const_iterator iterator;

    for (iterator = bullets.begin(); iterator != bullets.end(); ++iterator) {
        (*iterator)->Display();
    }

    for (iterator = explosions.begin(); iterator != explosions.end(); ++iterator) {
        (*iterator)->Display();
    }

    for (iterator = enemyBullet.begin(); iterator != enemyBullet.end(); ++iterator) {
        (*iterator)->Display();
    }
}

void BulletManager::AddBlueBullet(int x, int y) {
    bullets.push_back(new BlueBullet(buffer, new Vector2(x, y), new Vector2(1, 0)));
}

void BulletManager::AddBlueBullet(Vector2* position, Vector2* direction) {
    bullets.push_back(new BlueBullet(buffer, position, direction));
}

void BulletManager::AddEnemyBullet(Vector2* position, Vector2* direction) {
    enemyBullet.push_back(new RedCrossBullet(buffer, position, direction));
}

void BulletManager::AddExplosion(Vector2* position) {
    explosions.push_back(new ExplosionBullet(buffer, position));
}

void BulletManager::InitializeGraphics() {
    Bullet* b = new BlueBullet(buffer, new Vector2(0, 0), new Vector2(0, 0));
    RedCrossBullet* r = new RedCrossBullet(buffer, new Vector2(0, 0), new Vector2(0, 0));
    ExplosionBullet* e = new ExplosionBullet(buffer, new Vector2(0, 0));
    delete b;
    delete r;
    delete e;
}

void BulletManager::HandleCollisionWithEnemy(EnemyManager* enemyManager, GameData* data, Ship* ship, Audio* audio) {
    std::list<Bullet*>::const_iterator bulletIterator;
    for (bulletIterator = bullets.begin(); bulletIterator != bullets.end(); ++bulletIterator) {
        SDL_Rect rect = (*bulletIterator)->GetCollisionBox();

        std::list<Enemy*>::const_iterator enemyIterator;
        for (enemyIterator = enemyManager->Enemies.begin(); enemyIterator != enemyManager->Enemies.end(); ++enemyIterator) {
            if ((*enemyIterator)->Collision(&rect))
            {
                (*enemyIterator)->ApplyDamage((*bulletIterator)->Force);
                if(!(*enemyIterator)->IsAlive()) {
                    this->AddExplosion(new Vector2((*bulletIterator)->x, (*bulletIterator)->y));
                    data->AddPoints((*enemyIterator)->Points);
                    audio->PlayExplosionSfx();
                }
                (*bulletIterator)->HasHit = true;
            }
        }
    }

    for (bulletIterator = enemyBullet.begin(); bulletIterator != enemyBullet.end(); ++bulletIterator) {
        SDL_Rect rect = (*bulletIterator)->GetCollisionBox();
        if(ship->Collision(&rect) && ship->Imune <= 0)
        {
            this->AddExplosion(new Vector2((*bulletIterator)->x, (*bulletIterator)->y));
            data->SetLife(data->GetLife() - 1);
            ship->Imune = 30;
            (*bulletIterator)->HasHit = true;
            audio->PlayExplosionSfx();
            audio->PlayAlertSfx();
        }
    }

    std::list<Enemy*>::const_iterator enemyIterator;
    for (enemyIterator = enemyManager->Enemies.begin(); enemyIterator != enemyManager->Enemies.end(); ++enemyIterator) {
        if((*enemyIterator)->FrameSinceLastShot == (*enemyIterator)->Agressivity) {
            (*enemyIterator)->FrameSinceLastShot = 0;
            Vector2* adjustedPosition = new Vector2(ship->x - (*enemyIterator)->x, ship->y - (*enemyIterator)->y);
            AddEnemyBullet(new Vector2((*enemyIterator)->x, (*enemyIterator)->y), adjustedPosition->Normalize());
        }
        else
        {
            (*enemyIterator)->FrameSinceLastShot += 1;
        }

        SDL_Rect rect = (*enemyIterator)->GetCollisionBox();
        if (ship->Collision(&rect) && ship->Imune <= 0)
        {
            this->AddExplosion(new Vector2((*enemyIterator)->x, (*enemyIterator)->y));
            data->SetLife(data->GetLife() - 1);
            ship->Imune = 30;

            audio->PlayExplosionSfx();
            audio->PlayAlertSfx();

            (*enemyIterator)->ApplyDamage(10); 
            if (!(*enemyIterator)->IsAlive()) {
                this->AddExplosion(new Vector2((*enemyIterator)->x, (*enemyIterator)->y));
                data->AddPoints((*enemyIterator)->Points);

                audio->PlayExplosionSfx();
            }
        }
    }

    bullets.remove_if([enemyManager](Bullet* b) {
        if (b->HasHit) {
            delete b;
            return true;
        }
        return false;
    });

    enemyBullet.remove_if([enemyManager](Bullet* b) {
        if (b->HasHit) {
            delete b;
            return true;
        }
        return false;
    });

    explosions.remove_if([](Bullet* b) {
        return b->EndReached;
    });
}

void BulletManager::Reset() {
    std::list<Bullet*>::const_iterator bulletIterator;
    for (bulletIterator = bullets.begin(); bulletIterator != bullets.end(); ++bulletIterator) {
        delete (*bulletIterator);
    }

    for (bulletIterator = enemyBullet.begin(); bulletIterator != enemyBullet.end(); ++bulletIterator) {
        delete (*bulletIterator);
    }

    bullets.clear();
    enemyBullet.clear();
}



