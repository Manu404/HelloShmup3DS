#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include "input.h"
#include "ship.h"
#include "main.h"
#include "bullet.h"

Ship::Ship(SDL_Surface* buffer) : Sprite(SHIP_SPRITE, SHIP_ANIMATION_PER_ROW, SHIP_SPRITE_WIDTH, SHIP_SPRITE_HEIGHT, 100, 100, buffer){
    speed = SHIP_SPEED;
    frameSinceLastShot = 0;
    Imune = 0;
}

void Ship::HandleInput(InputMgmt* InputMgmt, BulletManager* bulletManager) {
    Ship::HandleShipMovement(InputMgmt);
    Ship::HandleFire(InputMgmt, bulletManager);
}

void Ship::HandleFire(InputMgmt* InputMgmt, BulletManager* bulletManager) {
    if (InputMgmt->IsKeyAPressed()) {
        if (frameSinceLastShot == 0) {
            bulletManager->AddBlueBullet(this->x, this->y);
        }

        frameSinceLastShot += 1;
        if (frameSinceLastShot == BLUE_BULLET_SHOT_SPEED)
            frameSinceLastShot = 0;
    }
}

void Ship::HandleShipMovement(InputMgmt* InputMgmt) {
    Vector2* vector = new Vector2(0, 0);

    if (InputMgmt->IsKeyUpPressed()) {
        this->SetAnimation(SHIP_ANIMATION_UP);
        vector->y -= speed;
    }
    if (InputMgmt->IsKeyDownPressed()) {
        this->SetAnimation(SHIP_ANIMATION_DN);
        vector->y += speed;
    }
    if (InputMgmt->IsKeyLeftPressed()) {
        this->SetAnimation(SHIP_ANIMATION_FT);
        vector->x -= speed;
    }
    if (InputMgmt->IsKeyRightPressed()) {
        this->SetAnimation(SHIP_ANIMATION_FT);
        vector->x += speed;
    }

    if (vector->x > 0 && (this->x + vector->x + SHIP_SPRITE_WIDTH) >= SCREEN_WIDTH)
        vector->x = 0;
    if (vector->x < 0 && (this->x < 0))
        vector->x = 0;

    if (vector->y > 0 && (this->y + vector->y + SHIP_SPRITE_HEIGHT - 16) >= SCREEN_HEIGHT)
        vector->y = 0;
    if (vector->y < 0 && (this->y) < 0)
        vector->y = 0;

    this->x += vector->x;
    this->y += vector->y;

    if (!InputMgmt->IsDirectionPressed())
        this->SetAnimation(SHIP_ANIMATION_FT);
}

void Ship::Display() {
    if (Imune > 0) {
        Imune -= 1;
        if (Imune % 3 == 0) {
            Sprite::Display();
        }
    }
    else {
        Sprite::Display();
    }
}

