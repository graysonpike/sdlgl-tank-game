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
    Sound full_sound;
    Sound accelerate_sound;
    Sound decelerate_sound;
    Channel *idle_channel;
    Channel *full_channel;
    Channel *accelerate_channel;
    bool running;
    bool accelerating;
    Timer accelerate_timer;

public:

    EngineSound(Scene *scene);
    EngineSound(Scene *scene, Sound idle_sound, Sound full_sound, Sound accelerate_sound, float accelerate_sound_duration);
    void update();
    void render();
    void start_engine();
    void stop_engine();
    void accelerate();
    void stop_accelerate();
};

#endif