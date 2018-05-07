#ifndef AUDIO_H
#define AUDIO_H
#include <SDL/SDL_mixer.h>

class Audio {
    int current_music_playing = 0;
    Mix_Music *title, *level;
    Mix_Chunk *alert, *explosion;
    void LoadAudio();
    void PlayMusic(Mix_Music* music);
    void PlaySfx(Mix_Chunk* chunk);
public:
    Audio();
    void PlayMusic(int id);
    void PlaySfx(int id);
    
    void PlayLevelMusic();
    void PlayTitleMusic();

    void PlayExplosionSfx();
    void PlayAlertSfx();
};

#endif