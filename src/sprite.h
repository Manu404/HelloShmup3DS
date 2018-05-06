#ifndef Sprite_H

#define Sprite_H

#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "core.h"

class Sprite {
        static std::map<char*, SDL_Surface*> surfaces;

        SDL_Surface* buffer;
        SDL_Rect viewPort;
        int currentRow;
        int currentFrame;
        int animationPerRow;
        int framePerAnimation;
        int animate;
        int currentAnimation;
        int offsetRow;
        int offsetColumn;
        int displayCollisionBox;
        int repeatAnimation;

        SDL_Surface* LoadSurfaceFromRomFs(char *path);
    public:
        int EndReached = false;
        SDL_Surface * image;
        float x, y;
        int width;
        int height;

        SDL_Surface* GetOrLoadSurface(char* path);

        Sprite(char* path, int animationPerRow, int framePerAnimation, int width, int height, float x, float y, SDL_Surface* buffer, int offsetRow, int offsetColumn, int displayCollisionBox, int repeatAnimation);
        Sprite(char* path, int animationPerRow, int width, int height, float x, float y, SDL_Surface* buffer) : Sprite(path, animationPerRow, 1, width, height, x, y, buffer, 0, 0, 0, 0) { }
        Sprite(char* path, Vector2* size, Vector2* position, Vector2* spriteOffset, SDL_Surface* buffer) : Sprite(path, 0, 30, size->x, size->y, position->x, position->y, buffer, spriteOffset->x, spriteOffset->y, 0, 1) { }
    
        ~Sprite();

        void Display(Vector2*);
        void Display();
        void Animate();
        void SetAnimation(int);
        void StartAnimation();
        void StopAnimation();
        int Collision(SDL_Rect* rect);
        SDL_Rect GetCollisionBox();
};
#endif