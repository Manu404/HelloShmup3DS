#ifndef Background_H
#define Background_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <list>

#define BG_WIDTH 512
#define BG_HEIGHT 256

class BackgroundLayer: public Sprite {
        int speed;
    public:
        BackgroundLayer(char*, int, int, int, SDL_Surface*);
        void Animate();
        void Display();
};

class Background {
        SDL_Surface* buffer;
    public:
        std::list<BackgroundLayer*> Layers;
        std::list<BackgroundLayer*> Overlay;
        Background(SDL_Surface*);
        ~Background();
        void Animate();
        void DisplayBackground();
        void DisplayOverlay();
};

class LevelBackground : public Background {
public:
    LevelBackground(SDL_Surface* buffer);
};

class TitleBackground : public Background {
public:
    TitleBackground(SDL_Surface* buffer);
};

#endif