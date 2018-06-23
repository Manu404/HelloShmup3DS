#include "level.h"
#include "main.h"
#include "game.h"

Level::Level(InputMgmt* im, UserInterface* ui, Audio* audio, SDL_Surface* backsurface) {
    this->im = im;
    this->ui = ui;
    this->audio = audio;
    this->backsurface = backsurface;

    this->CreateLevelObject();
}

void Level::Run(SDL_Surface* screen) {
    this->ResetLevel();

    while (is_level_running) {

        printf("ok");

        im->HandleEvent();

        if (data->GetLife() > 0) {
            this->Run();
        }
        else {
            this->RunGameOver();
        }

        SDL_BlitSurface(backsurface, NULL, screen, NULL);

        SDL_Flip(screen);
    }
}

void Level::Run() {
    frame += 1;

    audio->PlayLevelMusic();

    ship->HandleInput(im, bulletManager);

    if (im->Disabled > 0) {
        im->Disabled -= 1;
        return;
    }

    if (im->IsKeyStartPressed() && !is_paused) {
        is_paused = true;
        im->Disabled = InputWaitFrame;
        return;
    }

    if (im->IsKeyStartPressed() && is_paused) {
        is_paused = false;
        im->Disabled = InputWaitFrame;
        return;
    }

    if (is_paused) {
        ui->DisplayPause();
        return;
    }

    AnimateLevel();

    bulletManager->HandleCollisionWithEnemy(enemyManager, data, ship, audio);

    if (frame % 30 == 0) {
        GenerateEnemy();
    }

    DisplayLevel();

}

void Level::AnimateLevel() {
    levelBackground->Animate();
    enemyManager->Animate();
    bulletManager->Animate();
    ship->Animate();
}

void Level::DisplayLevel() {
    levelBackground->DisplayBackground();
    enemyManager->Display();
    ship->Display();
    bulletManager->Display();
    levelBackground->DisplayOverlay();
    ui->Display(data);
}

void Level::GenerateEnemy() {
    Vector2* position = new Vector2(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 40));
    enemyManager->AddEnemy(1, position, 1);
    Vector2* adjustedPosition = new Vector2(ship->x - position->x, ship->y - position->y);
    bulletManager->AddEnemyBullet(position, adjustedPosition->Normalize());
}

void Level::RunGameOver() {
    ui->DisplayGameOver(data);
    if (im->IsKeyStartPressed()) {
        this->ResetLevel();
        im->Disabled = InputWaitFrame;
    }
    else if (im->IsKeySelectPressed()) {
        is_level_running = false;
        im->Disabled = InputWaitFrame;
    }
}

void Level::ResetLevel() {
    this->ship->Reset();
    this->bulletManager->Reset();
    this->enemyManager->Reset();
    this->levelBackground->Reset();
    this->data->Reset();

    this->is_level_running = 1;
}

void Level::DeleteLevelObjects() {
    delete this->levelBackground;
    delete this->bulletManager;
    delete this->enemyManager;
    delete this->ship;
    delete this->data;
}

void Level::CreateLevelObject() {
    this->ship = new Ship(this->backsurface);
    this->levelBackground = new LevelBackground(this->backsurface);
    this->bulletManager = new BulletManager(this->backsurface);
    this->enemyManager = new EnemyManager(this->backsurface);
    this->data = new GameData();

    this->bulletManager->InitializeGraphics();
    this->enemyManager->InitializeGraphics();
}