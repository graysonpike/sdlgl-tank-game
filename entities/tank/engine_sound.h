#ifndef SOUND_LOOPER_H
#define SOUND_LOOPER_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <sdlgl/game/entity.h>
#include <sdlgl/audio/sound.h>
#include <sdlgl/audio/audio.h>
#include <sdlgl/audio/channel.h>
#include <sdlgl/game/timer.h>


class EngineSound : public Entity {

    Sound idle_sound;
    Sound tracks_sound;
    Channel *idle_channel;
    Channel *tracks_channel;

public:

    explicit EngineSound(Scene *scene);
    EngineSound(Scene *scene, Sound idle_sound, Sound tracks_sound);
    void update() override;
    void render() override;
    void start_engine();
    void set_tracks_volume(float volume);
};

#endif