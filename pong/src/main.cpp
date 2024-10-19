#include <algorithm>
#include "raylib.h"

#include "IScene.hpp"
#include "PongGame.hpp"
#include "PongMenu.hpp"

enum Scene {
    MENU = 0,
    GAME,
};

typedef struct State {
    Scene scene;
    IScene* currentScene;
    PongGame game;
    PongMenu menu;
} State;

void init_state(State& state) {
    state.scene = MENU;
    state.currentScene = &state.menu;
}

void update(State& state) {
    if (state.currentScene->changeScene) {
        state.currentScene->on_exit();

        switch (state.scene) {
            case MENU:
                state.scene = GAME;
                state.currentScene = &state.game;
                break;
            default:
                state.scene = MENU;
                state.currentScene = &state.menu;
                break;
        }
                
        state.currentScene->on_enter();
    }

    state.currentScene->update(std::min(GetFrameTime(), 0.16666f));
}

void render(const State& state) {
    state.currentScene->draw();
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
    InitWindow(1080, 720, "CFB: Pong");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL); // don't close on escape key or any other key
    
    State state;
    init_state(state);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &state, 0, 1);
#else
    while (!WindowShouldClose()) {
        if (state.scene == MENU && IsKeyPressed(KEY_ESCAPE)) {
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
