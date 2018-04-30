#ifndef Sprite_H

#define Sprite_H

#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Sprite {
        static std::map<char*, SDL_Surface*> surfaces;

        SDL_Surface* buffer;
        SDL_Surface *image;
        SDL_Rect viewPort;
        int currentRow;
        int currentFrame;
        int animationPerRow;
        int framePerAnimation;
        int animate;
        int currentAnimation;

        SDL_Surface* GetOrLoadSurface(char* path);
        SDL_Surface* LoadSurfaceFromRomFs(char *path);
    public:
        Sprite(char* path, int animationPerRow, int framePerAnimation, int width, int height, int x, int y, SDL_Surface* buffer);
        Sprite(char* path, int animationPerRow, int width, int height, int x, int y, SDL_Surface* buffer) : Sprite(path, animationPerRow, 30, width, height, x, y, buffer) { }
        ~Sprite();
        void Display(int, int);
        void Display();
        void Animate();
        void SetAnimation(int);
        void StartAnimation();
        void StopAnimation();
		
        int x;
        int y;
        int width;
        int height;
};
#endif