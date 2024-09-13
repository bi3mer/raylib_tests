#define DEBUG true

#include "raylib.h"
#include "app.hpp"

#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    
    void wasm_step(void* void_state) {
        App* app = static_cast<App*>(void_state);

        app->update(GetFrameTime());

        BeginDrawing();
        app->draw();
        EndDrawing();
    }
#endif

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "raylib Tests");
    SetTargetFPS(60);

    SetExitKey(KEY_NULL); // don't close on escape key or any other key

    App app;

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &app, 0, 1);
#else
    while (!WindowShouldClose() && app.isRunning) {
        app.update(GetFrameTime());
        
        BeginDrawing();
        app.draw();
        EndDrawing();
    }
#endif

    CloseWindow();
    return 0;
}