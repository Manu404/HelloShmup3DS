#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include "input.h"
#include "cat.h"

Cat::Cat() : Sprite("romfs:/cat.png", 3, 32, 32, 100, 100){
	speed = 7;
}

void Cat::HandleInput(InputManager* inputManager) {
	if(inputManager->IsKeyUpPressed()) {
		this->SetAnimation(3);
		this->y-= speed;
		printf("up\n");
	}
	if(inputManager->IsKeyDownPressed()) {
		this->SetAnimation(0);
		this->y+= speed;
		printf("dn\n");
	}	
	if(inputManager->IsKeyLeftPressed()) {
		this->SetAnimation(1);
		this->x-= speed;
		printf("lt\n");
	}
	if(inputManager->IsKeyRightPressed()) {
		this->SetAnimation(2);
		this->x+= speed;
		printf("up\n");
	}
	
	if(inputManager->IsDirectionPressed())
		this->StartAnimation();
	else
		this->StopAnimation();
}