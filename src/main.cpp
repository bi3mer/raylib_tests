#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define DEBUG true

#include "scene_menu.hpp"

int main() {
    InitWindow(1080, 720, "raylib Tests");
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    Scene* scene;
    SceneMenu menu;

    scene = &menu;

    while (!WindowShouldClose()) {
        Scene* new_scene = scene->change_scene();
        if (new_scene != nullptr) {
            scene->on_exit();
            new_scene->on_enter();
            scene = new_scene;
        }

        scene->update(GetFrameTime());

        BeginDrawing();
        scene->draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}