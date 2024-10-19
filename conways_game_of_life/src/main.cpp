#include "raylib.h"
#include "Conway.hpp"

typedef struct State {
    float time;
    Conway<100> conway;
} State;

void init_state(State& state) {
    state.time = 0;
}

void update(State& state) {
    state.time += GetFrameTime();

    if (state.time > 0.075f) {
        state.time = 0;
        state.conway.step();
    }
}

void render(const State& state) {
    const float W = (float) GetScreenWidth();
    const float H = (float) GetScreenHeight();
    
    // Draw the grid
    ClearBackground(RAYWHITE);

    const float start_x = W * 0.1f;
    const float x_mod = (W*0.9f - start_x) / 100.0f;

    const float start_y = H * 0.1f;
    const float y_mod = (H*0.9f - start_y) / 100.0f;

    const float mod = std::min(x_mod, y_mod);

    float y_pos = H*0.1f;
    for(std::size_t y = 0; y < 100; ++y, y_pos+=mod) {
        float x_pos = W*0.1;
        for(std::size_t x = 0; x < 100; ++x, x_pos+=mod) {
            if (state.conway.cellIsActive(y, x)) {
                DrawRectangle(x_pos, y_pos, mod-1, mod-1, BLACK);
            }
        }
    }

    DrawText("Conway's Game of Life", start_x, start_y-30, 20, BLACK);
}

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
    InitWindow(1080, 720, "raylib Tests");
    SetTargetFPS(60);

    State state;
    init_state(state);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &state, 0, 1);
#else
    while (!WindowShouldClose()) {
        update(state);

        BeginDrawing();
        render(state);
        EndDrawing();
    }
#endif

    CloseWindow();
    return 0;
}
