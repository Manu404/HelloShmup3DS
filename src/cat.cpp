#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include "input.h"
#include "cat.h"

Cat::Cat() : Sprite("romfs:/cat.png", CAT_FRAME_PER_ANIMATION, CAT_SPRITE_WIDTH, CAT_SPRITE_HEIGHT, 100, 100){
	speed = CAT_SPEED;
}

void Cat::HandleInput(InputManager* inputManager) {
	if(inputManager->IsKeyUpPressed()) {
		this->SetAnimation(CAT_ANIMATION_UP);
		this->y-= speed;
	}
	if(inputManager->IsKeyDownPressed()) {
		this->SetAnimation(CAT_ANIMATION_DN);
		this->y+= speed;
	}	
	if(inputManager->IsKeyLeftPressed()) {
		this->SetAnimation(CAT_ANIMATION_LT);
		this->x-= speed;
	}
	if(inputManager->IsKeyRightPressed()) {
		this->SetAnimation(CAT_ANIMATION_RT);
		this->x+= speed;
	}
	
	if(inputManager->IsDirectionPressed())
		this->StartAnimation();
	else
		this->StopAnimation();
}