#define DEBUG true

#include "raylib.h"
#include "raymath.h"
#include <algorithm>

const Vector2 G = { 0, 1 };

typedef struct State {
    bool pause;
    float radius;
    Vector2 pos;
    Vector2 velocity;
} State;

void init_state(State& state) {
    state.pause = false;
    state.pos = { 0.5f, 0.5f};
    state.velocity = {
        0.25f + ((float)(rand()) / (float)(RAND_MAX)) / 5,
        0.1f + ((float)(rand()) / (float)(RAND_MAX)) / 5
    };

    state.radius = 0.02f;
}

void update(State& state) {
    if (IsKeyPressed(KEY_SPACE)) {
        state.pause = !state.pause;
    }

    if (state.pause) return;

    // simulate 3 steps
    const float dt = std::min(GetFrameTime(), 0.16666f)  / 3.0;
    const Vector2 gravity = Vector2Scale(G, dt);

    for (uint_fast8_t i = 0; i < 3; ++i) {
        state.velocity = Vector2Add(state.velocity, gravity);
        state.pos = Vector2Add(state.pos, Vector2Scale(state.velocity, dt));

        if (state.pos.x - state.radius < 0.0f) {
            state.pos.x = state.radius;
            state.velocity.x = -state.velocity.x;
        } else if (state.pos.x + state.radius >= 1.0f) {
            state.pos.x = 1.0f - state.radius;
            state.velocity.x = -state.velocity.x;
        }

        if (state.pos.y + state.radius >= 1.0f) {
            state.pos.y = 1.0f - state.radius;
            state.velocity.y = -state.velocity.y;
        }
    } 
}

void render(const State& state) {
    const float W = (float) GetScreenWidth();
    const float H = (float) GetScreenHeight();
    const float min = std::min(H, W); 

    const float start = 0.1f*min;
    const float end = 0.9f*min;

    ClearBackground(BLACK);

    DrawRectangle(start, start, 0.8f*min, 0.8f*min, GRAY);
    DrawCircle(
        Lerp(start, end, state.pos.x),
        Lerp(start, end, state.pos.y),
        min*state.radius,
        BLACK
    );

    DrawText("Press space to pause and unpause.", 10, 10, 20, RAYWHITE);

    if (state.pause) {
        Vector2 dimension = MeasureTextEx(GetFontDefault(), "PAUSED", 30, 1);
        DrawText(
            "PAUSED", 
            (start + end - dimension.x) / 2.0f, 
            (start + end - dimension.y) / 2.0f, 
            30, 
            BLACK
        );
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
