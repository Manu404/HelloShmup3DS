#ifndef Cat_H
#define Cat_H
#include "sprite.h"
#include "input.h"

class Cat: public Sprite {
		int speed;
	public:
		Cat();
		void HandleInput(InputManager*);
};

#endif