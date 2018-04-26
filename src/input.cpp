#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "input.h"

InputManager::InputManager() {
    SDL_JoystickOpen(0);
    SDL_N3DSKeyBind(KEY_CPAD_UP|KEY_CSTICK_UP, SDLK_UP);
    SDL_N3DSKeyBind(KEY_CPAD_DOWN|KEY_CSTICK_DOWN, SDLK_DOWN);
    SDL_N3DSKeyBind(KEY_CPAD_LEFT|KEY_CSTICK_LEFT, SDLK_LEFT);
    SDL_N3DSKeyBind(KEY_CPAD_RIGHT|KEY_CSTICK_RIGHT, SDLK_RIGHT);
	this->Reset();
}

int InputManager::IsKeyDownPressed() {
    return key_held[K_DN];
}

int InputManager::IsKeyUpPressed() {
    return key_held[K_UP];
}

int InputManager::IsKeyLeftPressed() {
    return key_held[K_LT];
}

int InputManager::IsKeyRightPressed() {
    return key_held[K_RT];
}

int InputManager::IsDirectionPressed() {
    return key_held[K_LT] || key_held[K_RT] || key_held[K_DN] || key_held[K_UP];
}

void InputManager::Reset() {
    key_held[K_UP] = 0;
    key_held[K_DN] = 0;
    key_held[K_LT] = 0;
    key_held[K_RT] = 0;
}

int InputManager::HandleEvent() {
    static SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    key_held[K_UP] = 1;
                    printf("up\n");
                    break;
                case SDLK_DOWN:
                    key_held[K_DN] = 1;
                    printf("down\n");
                    break;
                case SDLK_LEFT:
                    key_held[K_LT] = 1;
                    printf("left\n");
                    break;
                case SDLK_RIGHT:
                    key_held[K_RT] = 1;
                    printf("right\n");
                    break;
            }
        }	
        if(event.type == SDL_KEYUP) {
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    key_held[K_UP] = 0;
                    printf("up released\n");
                    break;
                case SDLK_DOWN:
                    key_held[K_DN] = 0;
                    printf("down released\n");
                    break;
                case SDLK_LEFT:
                    key_held[K_LT] = 0;
                    printf("left released\n");
                    break;
                case SDLK_RIGHT:
                    key_held[K_RT] = 0;
                    printf("right released\n");
                    break;
            }
        }
    }
}