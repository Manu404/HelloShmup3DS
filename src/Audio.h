#ifndef AUDIO_H
#define AUDIO_H
#include <SDL/SDL_mixer.h>

#define MUSIC_LEVEL 1
#define MUSIC_TITLE 2

#define SFX_EXPLOSION 1
#define SFX_ALERT 2

class Audio {
    int current_music_playing = 0;
    Mix_Music *title, *level;
    Mix_Chunk *alert, *explosion;
    void LoadAudio();
    Mix_Music* LoadMus(const char * file);
    Mix_Chunk* LoadWav(const char * file);
    void PlayMusic(Mix_Music* music);
    void PlaySfx(Mix_Chunk* chunk);
    void PlayMusic(int id);
    void PlaySfx(int id);
public:
    Audio();
    
    void PlayLevelMusic();
    void PlayTitleMusic();

    void PlayExplosionSfx();
    void PlayAlertSfx();
};

#endif