#pragma once
#include "scenes.hpp"

typedef struct State {
    bool show_instructions;
    Scene current_scene;
    int lives;
    float time;
} State;


void init_state(State&); 
void initialize_state_for_game(State&);
