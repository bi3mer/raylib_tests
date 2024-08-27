#include <stdio.h>
#include <cstdint>
#include <algorithm>

#include "raylib.h"
#include "Hilbert.hpp"
#include <vector>

enum State {
    HILBERT,
    PAUSE
};

typedef struct SimulationState {
    Hilbert hilbert;
    std::vector<Vector2> points;
    State state;
    float time;
} SimulationState;

void draw_path(SimulationState* state) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    const float x_length = W / (float) state->hilbert.N;
    const float y_length = H / (float) state->hilbert.N;

    Vector2 p = state->points[0];
    Vector2 last_point = {
        p.x * x_length + x_length / 2.0f,
        p.y * y_length + y_length / 2.0f
    };

    for (std::size_t i = 1; i < state->points.size(); ++i) {
        p = state->points[i];
        const float x = p.x * x_length + x_length/2.0f;
        const float y = p.y * y_length + y_length/2.0f;

        DrawLineEx({x ,y}, last_point, 2, RED);

        last_point.x = x;
        last_point.y = y;
    }

    EndDrawing();
}

void state_hilbert(SimulationState* state) {
    if(!state->hilbert.is_done()) {
        state->points.push_back(state->hilbert.generate_next());
    } else {
        state->state = PAUSE;
    }
}

void state_pause(SimulationState* state) {
    state->time += GetFrameTime();
    if (state->time > 1.0f) {
        state->hilbert.increase_order();
        state->points.clear();
        state->points.push_back(POSITIONS[0]);

        state->time = 0.0f;
        state->state = HILBERT;
    } 
}

void step(SimulationState* state) {
    switch(state->state) {
        case HILBERT: {
            state_hilbert(state);
            break;
        }
        case PAUSE: {
            state_pause(state);
            break;
        }
        default: {
            printf("Unhandled state type: %i\n", state);
            exit(1);
        }
    }

    draw_path(state);
}

#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    
    void wasm_step(void* void_state ) {
        step(static_cast<SimulationState*>(void_state));
    }
#endif

int main(void) {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(512, 512, "Hilbert Curves");


    Hilbert hilbert(1);
    std::vector<Vector2> points;
    points.push_back(POSITIONS[0]);
    SimulationState state = {hilbert, points, HILBERT, 0.0f};

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &state, 0, 1);
#else
    while (!WindowShouldClose()) {
        step(&state);
    }
#endif
    
    CloseWindow();

    return 0;
}