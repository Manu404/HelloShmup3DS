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
        std::list<BackgroundLayer*> layers;
        std::list<BackgroundLayer*> overlay;
    public:
        Background(SDL_Surface*);
        ~Background();
        void Animate();
        void DisplayBackground();
        void DisplayOverlay();
};

#endif