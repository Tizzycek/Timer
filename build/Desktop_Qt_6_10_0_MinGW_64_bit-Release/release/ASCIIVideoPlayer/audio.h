//
// Created by Tiziano on 21.07.2025.
//

#ifndef AUDIO_H
#define AUDIO_H

#ifdef _WIN32
#include "SDL2/include/SDL2/SDL.h"
#include "SDL2/include/SDL2/SDL_mixer.h"
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif
#include <iostream>
#include <stdexcept>

class Audio {
private:
    Mix_Music* music = nullptr;
    const std::string*path;

public:
    explicit Audio(const std::string&);
    static void initialize();
    void startAudio();
    void playAudio() const;
    ~Audio();
};

#ifdef __cplusplus
extern "C" {
#endif

    extern int check_stop();

#ifdef __cplusplus
}
#endif

#endif //AUDIO_H
