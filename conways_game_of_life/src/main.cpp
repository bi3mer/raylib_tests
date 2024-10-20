#include "raylib.h"
#include "Conway.hpp"

#define GRID_SIZE 100

typedef struct State {
    float time;
    Conway<GRID_SIZE> conway;
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

    const float min = std::min(H, W); 
    const float grid_length = 0.8f* min;
     
    float startX;
    float startY;

    if (H > W) {
        startX = 0.1f*min;
        startY = (H - grid_length) / 2;
    } else {
        startY = 0.1f*min;
        startX = (W - grid_length) / 2;
    }

    const float cell_dimension = grid_length / GRID_SIZE;
    
    // Draw the grid
    ClearBackground(BLACK);

    /*const float start_x = W * 0.1f;*/
    /*const float x_mod = (W*0.9f - start_x) / GRID_SIZE.0f;*/
    /**/
    /*const float start_y = H * 0.1f;*/
    /*const float y_mod = (H*0.9f - start_y) / GRID_SIZE.0f;*/

    /*const float mod = std::min(x_mod, y_mod);*/

    for(std::size_t y = 0; y < GRID_SIZE; ++y) {
        float y_pos = startY + y*cell_dimension;
        for(std::size_t x = 0; x < GRID_SIZE; ++x) {
            if (state.conway.cellIsActive(y, x)) {
                DrawRectangle(
                    startX + x*cell_dimension, 
                    y_pos, 
                    cell_dimension - 1,
                    cell_dimension - 1, 
                    RED
                );
            }
        }
    }

    DrawText("Conway's Game of Life", startX, startY - 30, 20, RAYWHITE);
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
    InitWindow(1080, 720, "CFB: Conway's Game of Life");
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
