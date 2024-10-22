#include "state.hpp"
#include "box2d/b2_world.h"
#include <cstdio>

State::State() : world({0, 0}) {
    show_instructions = true;
    current_scene = Scene::MENU;

}

State::~State() {
    /*b2DestroyWorld(world_id);*/
}

void State::set_up_for_game() {
    printf("state::set_up_for_game not yet implemented\n");
}
