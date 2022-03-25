#include "engine_sound.h"
#include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>


EngineSound::EngineSound(Scene *scene) : Entity(scene) {}


EngineSound::EngineSound(
        Scene *scene,
        Sound idle_sound,
        Sound tracks_sound,
        Sound accelerate_sound,
        float accelerate_sound_duration
) :
        Entity(scene),
        accelerating(false),
        idle_sound(idle_sound),
        tracks_sound(tracks_sound),
        accelerate_sound(accelerate_sound),
        accelerate_timer(accelerate_sound_duration),
        idle_channel(scene->get_audio()->reserve_channel()),
        tracks_channel(scene->get_audio()->reserve_channel())
{}


void EngineSound::update() {}


void EngineSound::render() {};


void EngineSound::start_engine() {
    idle_channel->play_sound(idle_sound, true);
}


void EngineSound::accelerate() {
    if (accelerating) { return; }
    accelerate_timer.reset();
    accelerating = true;
    accelerate_channel = scene->get_audio()->play_sound(accelerate_sound);
    accelerate_channel->set_volume(1.0f);
    tracks_channel->set_volume(0.0f);
    tracks_channel->play_sound(tracks_sound, true);
}


void EngineSound::stop_accelerate() {
    if (!accelerating) { return; }
    accelerating = false;
    if (accelerate_timer.is_active()) {
        accelerate_channel->fade_rate(0.0f, -1.0f);
    }
}


void EngineSound::set_tracks_volume(float volume) {
    tracks_channel->set_volume(volume);
}
