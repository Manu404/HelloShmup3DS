#include "Audio.h";

Audio::Audio()
{
    this->LoadAudio();
}

void Audio::PlayMusic(Mix_Music* music) {
    /*if (Mix_PlayingMusic() != 0) {
        Mix_HaltMusic();
    }*/
    Mix_HaltMusic();
    Mix_PlayMusic(music, -1);
}

void Audio::PlaySfx(Mix_Chunk* chunk) {
    Mix_PlayChannel(0, chunk, 0);
}

void Audio::PlayMusic(int id) {
    if (id == this->current_music_playing) return;
    this->current_music_playing = id;
    switch(id) {
        case 1: this->PlayMusic(this->title); break;
        case 2: this->PlayMusic(this->level); break;
    }
}

void Audio::PlaySfx(int id) {
    switch (id) {
        case 1: this->PlaySfx(this->alert); break;
        case 2: this->PlaySfx(this->explosion); break;
    }
}

void Audio::LoadAudio() {
    title = Mix_LoadMUS("romfs:/music/title.wav");    
    if (!title) {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }

    level = Mix_LoadMUS("romfs:/music/level.wav");
    if (!level) {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }

    alert = Mix_LoadWAV("romfs:/sfx/alert.wav");
    if (!alert) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }

    explosion = Mix_LoadWAV("romfs:/sfx/explosion.wav");
    if (!explosion) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
}


void Audio::PlayLevelMusic() {
    this->PlayMusic(2);
}

void Audio::PlayTitleMusic() {
    this->PlayMusic(1);
}

void Audio::PlayAlertSfx() {
    this->PlaySfx(1);
}

 void Audio::PlayExplosionSfx() {
     this->PlaySfx(2);
 }



