#include "audio.h"

Audio::Audio(const std::string& path) {
    this->path = &path;
}

Audio::~Audio() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
};

void Audio::initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        throw std::runtime_error(std::string("SDL non può inizializzarsi: ") + SDL_GetError());

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        throw std::runtime_error(std::string("SDL_mixer non può inizializzarsi: ") + Mix_GetError());

    atexit([] {
        SDL_Quit();
        Mix_CloseAudio();
    });
}


void Audio::playAudio() const {
    if (Mix_PlayMusic(music, 0) == -1)
        throw std::runtime_error(std::string("Errore durante la riproduzione della musica: ") + Mix_GetError());

    while (Mix_PlayingMusic() && !check_stop()) {
        SDL_Delay(100);
    }
}

void Audio::startAudio() {
    initialize();

    music = Mix_LoadMUS(path->c_str());

    if (!music)
        throw std::runtime_error(std::string("Impossibile caricare l'audio: ") + Mix_GetError());

}
