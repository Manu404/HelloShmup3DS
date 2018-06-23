#include "title.h"
#include "game.h"

Title::Title(SDL_Surface* backsurface, UserInterface* ui, Audio* audio, InputMgmt *im) {
    this->backsurface = backsurface;
    this->ui = ui;
    this->audio = audio;
    this->im = im;
    title_background = new TitleBackground(this->backsurface);
}

void Title::Run(SDL_Surface* screen) {
   while (true) {
        frame += 1;
        
        im->HandleEvent();

        title_background->Animate();

        title_background->DisplayBackground();
        ui->DisplayTitle();
        title_background->DisplayOverlay();

        SDL_BlitSurface(backsurface, NULL, screen, NULL);

        SDL_Flip(screen);


        if (im->Disabled) {
            im->Disabled -= 1;
            continue;
        }
        if (im->IsKeyStartPressed() || im->IsKeyAPressed()) {
            im->Disabled = InputWaitFrame;
            return;
        }
        if (im->IsKeySelectPressed()) {
            game_running = 0;
            return;
        }
    }
}

