#include "scene_menu.hpp"
#include "raylib.h"
#include "raygui.h"

void SceneMenu::draw() {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Show Message")) {
        this->showMessageBox = true;
    }

    if (showMessageBox) {
        int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) {
            showMessageBox = false;
        }
    }
};