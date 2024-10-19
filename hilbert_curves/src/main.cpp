#include <vector>
#include "raylib.h"

#include "Hilbert.hpp"

enum class HilbertState {
    HILBERT,
    PAUSE
};

typedef struct State {
    HilbertState state;
    float time;
    Hilbert hilbert;
    std::vector<Vector2> points;
} State;

void init_state(State& state) {
    state.time = 0.0f;
    state.state = HilbertState::HILBERT;
    state.points.push_back(HILBERT_POSITIONS[0]);
}

void update(State& state) {
    const float dt = GetFrameTime();

    switch(state.state) {
        case HilbertState::HILBERT: {
            if(state.hilbert.is_done()) {
                state.state = HilbertState::PAUSE;
            } else {
                state.points.push_back(state.hilbert.generate_next());
            }

            break;
        }
        case HilbertState::PAUSE: {
            state.time += dt;
            if (state.time > 1.0f) {
                state.time = 0.0f;
                state.state = HilbertState::HILBERT;
                state.hilbert.increase_order();

                state.points.clear();
                state.points.push_back(HILBERT_POSITIONS[0]);
            } 

            break;
        }
        default: {
            printf("Unhandled state type: %d\n", (int) state.state);
            exit(1);
        }
    }
}

void render(const State& state) {
    ClearBackground(BLACK);

    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    const float x_length = W / (float) state.hilbert.N;
    const float y_length = H / (float) state.hilbert.N;

    Vector2 p = state.points[0];
    Vector2 last_point = {
        p.x * x_length + x_length / 2.0f,
        p.y * y_length + y_length / 2.0f
    };

    for (std::size_t i = 1; i < state.points.size(); ++i) {
        p = state.points[i];
        const float x = p.x * x_length + x_length/2.0f;
        const float y = p.y * y_length + y_length/2.0f;

        DrawLineEx({x ,y}, last_point, 2, RED);

        last_point.x = x;
        last_point.y = y;
    }
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
    InitWindow(1080, 720, "CFB: Hilbert Curves");
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
