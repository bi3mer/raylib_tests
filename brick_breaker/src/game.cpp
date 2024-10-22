#include "game.hpp"
#include "scenes.hpp"

#include "raylib.h"
#include <cstdio>

void game_update(State& state) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        state.current_scene = Scene::MENU;
        return;
    }

    printf("game_update not yet implemented\n");
}

void game_render(const State& state) {
    printf("game_render not yet implmeented\n");
}
