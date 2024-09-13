#define DEBUG true

#include "raylib.h"
#include "app.hpp"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "raylib Tests");
    SetTargetFPS(60);

    SetExitKey(KEY_NULL); // don't close on escape key or any other key

    App app;
    while (!WindowShouldClose() && app.isRunning) {
        app.update(GetFrameTime());
        
        BeginDrawing();
        app.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}