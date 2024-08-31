#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define DEBUG true

#include "scene_menu.hpp"

int main() {
    InitWindow(1080, 720, "Hilbert Curves");
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    SceneMenu menu;

    bool showMessageBox = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        menu.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}