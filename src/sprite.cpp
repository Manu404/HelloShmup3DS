#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include <iostream>
#include <map>

std::map<char*, SDL_Surface*> Sprite::surfaces;

Sprite::Sprite(char* path, int animationPerRow, int framePerAnimation, int width, int height, int x, int y, SDL_Surface* buffer) {
    this->framePerAnimation = framePerAnimation;
    this->animationPerRow = animationPerRow;
    this->currentAnimation = 0;
    this->currentRow = 0;
    this->currentFrame = 0;
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->buffer = buffer;
    this->image = this->GetOrLoadSurface(path);
    if (this->image == NULL) {
        printf("Can't load image");
    }
}

Sprite::~Sprite() {
    SDL_FreeSurface(this->image);
    printf("free sprite\n");
}

SDL_Surface* Sprite::GetOrLoadSurface(char* path) {
    if (surfaces.find(path) != surfaces.end()) {
        printf("recycle surface %s\n", path);
        return surfaces[path];
    }
    else {
        printf("load surface %s\n", path);
        surfaces.insert(std::make_pair(path, LoadSurfaceFromRomFs(path)));
        return surfaces[path];
    }
}

SDL_Surface* Sprite::LoadSurfaceFromRomFs(char* path) {
    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    else {
        optimizedSurface = SDL_DisplayFormatAlpha(loadedSurface);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

void Sprite::Display(int x, int y) {
    SDL_Rect srcrect = { currentAnimation * width, currentRow * height, width, height };
    SDL_Rect dstrect = { x, y, width, height };
    SDL_BlitSurface(image, &srcrect, buffer, &dstrect);
}

void Sprite::Animate() {
    if(animate) {
        currentFrame += 1;
        if (currentFrame > framePerAnimation) {
            currentAnimation += 1;
            currentFrame = 0;
        }
        if (currentAnimation > animationPerRow) {
            currentAnimation = 0;
        }
    }
}

void Sprite::Display() {
    this->Display(this->x, this->y);
}

void Sprite::SetAnimation(int animation) {
    currentRow = animation;
}

void Sprite::StartAnimation() {
    animate = 1;
}

void Sprite::StopAnimation() {
    animate = 0;
}