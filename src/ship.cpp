#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include "input.h"
#include "ship.h"
#include "main.h"

Ship::Ship(SDL_Surface* buffer) : Sprite("romfs:/ship.png", Ship_FRAME_PER_ANIMATION, Ship_SPRITE_WIDTH, Ship_SPRITE_HEIGHT, 100, 100, buffer){
    speed = Ship_SPEED;
}

void Ship::HandleInput(InputManager* inputManager) {
    int xvector = 0;
    int yvector = 0;
	
    if(inputManager->IsKeyUpPressed()) {
        this->SetAnimation(Ship_ANIMATION_UP);
        yvector -= speed;
    }
    if(inputManager->IsKeyDownPressed()) {
        this->SetAnimation(Ship_ANIMATION_DN);
        yvector += speed;
    }	
    if(inputManager->IsKeyLeftPressed()) {
        this->SetAnimation(Ship_ANIMATION_FT);
        xvector-= speed;
    }
    if(inputManager->IsKeyRightPressed()) {
        this->SetAnimation(Ship_ANIMATION_FT);
        xvector+= speed;
    }
	
    if(xvector > 0 && (this->x + xvector + Ship_SPRITE_WIDTH) >= SCREEN_WIDTH)
        xvector = 0;
    if(xvector < 0 && (this->x < 0))
        xvector = 0;
	
    if(yvector > 0 && (this->y + yvector + Ship_SPRITE_HEIGHT - 16) >= SCREEN_HEIGHT)
        yvector = 0;
    if(yvector < 0 && (this->y) < 0)
        yvector = 0;
    
    this->x += xvector;
    this->y += yvector;
	
    if(!inputManager->IsDirectionPressed())
        this->SetAnimation(Ship_ANIMATION_FT);
}