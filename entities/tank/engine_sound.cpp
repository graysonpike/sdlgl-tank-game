#include "engine_sound.h"
#include <sdlgl/utilities/math.h>


EngineSound::EngineSound(Scene *scene) : Entity(scene) {}


EngineSound::EngineSound(
        Scene *scene,
        Sound idle_sound,
        Sound tracks_sound,
        Sound turret_rotate_sound,
        float volume
) :
        Entity(scene),
        idle_sound(idle_sound),
        tracks_sound(tracks_sound),
        turret_rotate_sound(turret_rotate_sound),
        idle_channel(scene->get_audio()->reserve_channel()),
        tracks_channel(scene->get_audio()->reserve_channel()),
        turret_rotate_channel(scene->get_audio()->reserve_channel()),
        volume(volume)
{}


void EngineSound::update() {}


void EngineSound::render() {};


void EngineSound::start_engine() {
    idle_channel->play_sound(idle_sound, true, volume);
    tracks_channel->play_sound(tracks_sound, true, 0.0f);
    turret_rotate_channel->play_sound(turret_rotate_sound, true, 0.0f);
}


void EngineSound::set_tracks_intensity(float intensity) {
    tracks_channel->set_volume(intensity * volume);
}


void EngineSound::set_turret_rotating(bool rotating) {
    if (rotating) {
        turret_rotate_channel->set_volume(volume * 0.8f);
    }
    else {
        turret_rotate_channel->set_volume(0.0f);
    }
}
