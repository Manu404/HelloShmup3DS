#include <3ds.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include <iostream>
#include <map>

std::map<char*, SDL_Surface*> Sprite::surfaces;

Sprite::Sprite(char* path, int animationPerRow, int framePerAnimation, int width, int height, float x, float y, SDL_Surface* buffer, int offsetRow, int offsetColumn, int displayCollisionBox, int repeatAnimation) {
    this->repeatAnimation = repeatAnimation;
    this->displayCollisionBox = displayCollisionBox;
    this->offsetColumn = offsetColumn;
    this->offsetRow = offsetRow;
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
    this->animate = 1;
    if (this->image == NULL) {
        printf("Can't load image");
    }
}

Sprite::~Sprite() {
    //SDL_FreeSurface(this->image);
    //printf("free sprite\n");
}

SDL_Surface* Sprite::GetOrLoadSurface(char* path) {
    if (surfaces.find(path) != surfaces.end()) {
        //printf("recycle surface %s\n", path);
        return surfaces[path];
    }
    else {
        //printf("load surface %s\n", path);
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
            //printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

void Sprite::Display(SDL_Surface* src, SDL_Rect* srcRect, SDL_Surface* dst, SDL_Rect* dstRect) {
    SDL_BlitSurface(src, srcRect, dst, dstRect);
}


void Sprite::Display() {
    this->Display(new Vector2(this->x, this->y));
}

void Sprite::Display(Vector2* vector) {
    SDL_Rect srcrect = { (currentAnimation + offsetColumn) * width, (currentRow + offsetRow) * height, width, height };
    SDL_Rect dstrect = { vector->x, vector->y, width, height };
    //SDL_BlitSurface(image, &srcrect, buffer, &dstrect);

    this->Display(image, &srcrect, buffer, &dstrect);

    if (this->displayCollisionBox) {
        SDL_Rect collisionBox = this->GetCollisionBox();
        SDL_FillRect(buffer, &collisionBox, SDL_MapRGB(buffer->format, 255, 0, 0));
    }
}

void Sprite::Animate() {
    if(animate) {
        currentFrame += 1;
        if (currentFrame > framePerAnimation) {
            currentAnimation += 1;
            currentFrame = 0;
        }
        if (currentAnimation > animationPerRow) {
            if (repeatAnimation)
                currentAnimation = 0;
            else {
                currentAnimation -= 1;
                EndReached = true;
            }
        }
    }
}

void Sprite::SetAnimation(int animation) {
    if (animation == currentRow) return;
    currentFrame = 0;
    currentAnimation = 0;
    currentRow = animation;
    EndReached = false;
}

void Sprite::StartAnimation() {
    currentFrame = 0;
    currentAnimation = 0;
    animate = 1;
    EndReached = false;
}

void Sprite::StopAnimation() {
    currentFrame = 0;
    currentAnimation = 0;
    animate = 0;
    EndReached = true;
}

SDL_Rect Sprite::GetCollisionBox() {
    return { x + width / 4, y + height / 4, width / 2, height / 2 };
}

int Sprite::Collision(SDL_Rect* rect) {
    SDL_Rect thisBox = this->GetCollisionBox();
    return !(thisBox.x > (rect->x + rect->w) ||
        (thisBox.x + thisBox.w) < rect->x ||
        thisBox.y > (rect->y + rect->h) ||
        (thisBox.y + thisBox.h) < rect->y);
}
