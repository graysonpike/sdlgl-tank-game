#include "engine_sound.h"
#include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>


EngineSound::EngineSound(Scene *scene) : Entity(scene) {}


EngineSound::EngineSound(
        Scene *scene,
        Sound idle_sound,
        Sound tracks_sound
) :
        Entity(scene),
        idle_sound(idle_sound),
        tracks_sound(tracks_sound),
        idle_channel(scene->get_audio()->reserve_channel()),
        tracks_channel(scene->get_audio()->reserve_channel())
{}


void EngineSound::update() {}


void EngineSound::render() {};


void EngineSound::start_engine() {
    idle_channel->play_sound(idle_sound, true);
    tracks_channel->set_volume(0.0f);
    tracks_channel->play_sound(tracks_sound, true);
}


void EngineSound::set_tracks_volume(float volume) {
    tracks_channel->set_volume(volume);
}
