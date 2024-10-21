#include "state.hpp"
#include <cstdio>

void init_state(State& state) {
    state.show_instructions = true;
    state.current_scene = Scene::MENU;
}

void initialize_state_for_game(State& state) {
    printf("initialize_state_for_game not yet implemented\n");
}
