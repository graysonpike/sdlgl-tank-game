#include "engine_sound.h"
#include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>


EngineSound::EngineSound(Scene *scene) : Entity(scene) {}


EngineSound::EngineSound(
        Scene *scene,
        Sound idle_sound,
        Sound full_sound,
        Sound accelerate_sound,
        float accelerate_sound_duration
) :
        Entity(scene),
        running(false),
        accelerating(false),
        idle_sound(idle_sound),
        full_sound(full_sound),
        accelerate_sound(accelerate_sound),
        accelerate_timer(accelerate_sound_duration),
        idle_channel(scene->get_audio()->reserve_channel()),
        full_channel(scene->get_audio()->reserve_channel())
{}


void EngineSound::update() {}


void EngineSound::render() {};


void EngineSound::start_engine() {
    running = true;
    idle_channel->play_sound(idle_sound, true);
}


void EngineSound::stop_engine() {
    running = false;
    idle_channel->stop_playing();
}


void EngineSound::accelerate() {
    if (accelerating) { return; }
    accelerate_timer.reset();
    accelerating = true;
    accelerate_channel = scene->get_audio()->play_sound(accelerate_sound);
    accelerate_channel->set_volume(1.0f);
    full_channel->fade_rate(0.0f, 1.0f, 3.0f);
    full_channel->play_sound(full_sound, true);
}


void EngineSound::stop_accelerate() {
    if (!accelerating) { return; }
    accelerating = false;
    if (accelerate_timer.is_active()) {
        accelerate_channel->fade_rate(0.0f, -1.0f);
    }
    full_channel->fade_rate(0.0f, -0.3f);
}
