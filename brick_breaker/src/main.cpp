#include <cstdio>
#include <cstdlib>

#include "raylib.h"
#include "state.hpp"
#include "menu.hpp"
#include "game.hpp"

/////////////////////// Game Logic  /////////////////////// 
void update(State& state) {
    switch(state.current_scene) {
    case GAME:
        game_update(state);
        break;
    case MENU:
    case LOST:
    case WON:
        menu_update(state);
        break;
    default:
        printf("Unhandled scene type in update: %d\n", (int) state.current_scene);
        exit(1);
    }
}

void render(const State& state) {
    ClearBackground(BLACK);

    switch (state.current_scene) {
    case GAME:
        game_render(state);
        break;
    case MENU:
    case LOST:
    case WON:
        menu_render(state);
        break;
    default:
        printf("Unhandled scene type in render: %d\n", (int) state.current_scene);
        exit(1);
    }
}

/////////////////////// WASM or Desktop Logic  ///////////////////////
#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    
    void wasm_step(void* void_state) {
        State* state = static_cast<State*>(void_state);

        update(*state);

        BeginDrawing();
        render(*state);
        EndDrawing();
    }
#endif

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "CFB: Snake");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    State state;
    init_state(state);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &state, 0, 1);
#else
    while (!WindowShouldClose()) {
        bool is_menu_state = state.current_scene == MENU || state.current_scene == WON || state.current_scene == LOST;
        if (is_menu_state && IsKeyPressed(KEY_ESCAPE)) {
            break;
        }

        update(state);

        BeginDrawing();
        render(state);
        EndDrawing();
    }
#endif

    CloseWindow();
    return 0;
}
