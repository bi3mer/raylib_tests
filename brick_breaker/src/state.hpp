#pragma once
#include "box2d/b2_world.h"
#include "scenes.hpp"

#include <Box2d/Box2d.h>

typedef struct State {
    // What scene is updating and rendering
    Scene current_scene;

    // menu variables
    bool show_instructions;
    float time;

    // game variables
    b2World world;

    // function definitions
    State();
    ~State();

    void set_up_for_game();
} State;
