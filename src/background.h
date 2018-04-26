#ifndef Background_H
#define Background_H
#include "sprite.h"
#include "input.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

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
        BackgroundLayer* layers[6];
    public:
        Background(SDL_Surface*);
        void Animate();
        void DisplayBackground();
        void DisplayOverlay();
};

#endif