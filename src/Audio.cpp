#include "Audio.h";

Audio::Audio()
{
    this->LoadAudio();
}

void Audio::PlayMusic(Mix_Music* music) {
    if (Mix_PlayingMusic() != 0) {
        Mix_HaltMusic();
    }
    Mix_PlayMusic(music, -1);
}

void Audio::PlaySfx(Mix_Chunk* chunk) {
    Mix_PlayChannel(-1, chunk, 0);
}

void Audio::PlayMusic(int id) {
    if (this->current_music_playing == id) return;
    this->current_music_playing = id;
    switch(id) {
        case MUSIC_TITLE: this->PlayMusic(this->title); break;
        case MUSIC_LEVEL: this->PlayMusic(this->level); break;
    }
}

void Audio::PlaySfx(int id) {
    switch (id) {
        case SFX_ALERT: this->PlaySfx(this->alert); break;
        case SFX_EXPLOSION: this->PlaySfx(this->explosion); break;
    }
}

void Audio::LoadAudio() {
    title = Audio::LoadMus("romfs:/music/level.mp3");
    level = Audio::LoadMus("romfs:/music/level.mp3");
    alert = Audio::LoadWav("romfs:/sfx/alert.wav");
    explosion = Audio::LoadWav("romfs:/sfx/explosion.wav");
}

Mix_Music* Audio::LoadMus(const char* file) {
    Mix_Music* music = Mix_LoadMUS(file);
    if (!music) {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }
    return music;
}

Mix_Chunk* Audio::LoadWav(const char* file) {
    Mix_Chunk* sfx = Mix_LoadWAV(file);
    if (!sfx) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
}

void Audio::PlayLevelMusic() {
    this->PlayMusic(MUSIC_LEVEL);
}

void Audio::PlayTitleMusic() {
    this->PlayMusic(MUSIC_TITLE);
}

void Audio::PlayAlertSfx() {
    this->PlaySfx(SFX_ALERT);
}

 void Audio::PlayExplosionSfx() {
     this->PlaySfx(SFX_EXPLOSION);
 }



