#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/resources.h>
#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/game/context.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/audio/audio.h>

#include "entities/tank/tiger/tiger.h"


void game_loop(Context context, Scene *scene) {

    context.inputs->update();
    context.clock->tick();
    context.graphics->clear_screen((SDL_Color){255, 255, 255, 255});

    scene->update(context.clock->get_delta());
    scene->render();

    context.audio->update(context.clock->get_delta());

    if (context.inputs->get_quit()) {
        *context.loop = false;
    }

    context.graphics->present_renderer(context.clock->get_delta());

}


int main() {

    Context context(new Graphics(1080, 720), new Audio(), new Inputs(), new Clock());
    Resources *resources = context.graphics->get_resources();

    // Load resources
    resources->load_resources("resources.json");

    // Create and populate scene
    Scene *scene = new Scene(context.graphics, context.audio, context.inputs);

    scene->add_entity(new Tiger(scene, 200, 200));

    while (*context.loop) {

        game_loop(context, scene);

    }

    return 0;
}
