#include "app.hpp"
#include "raygui.h"

#include "scene_000_frictionless_ball.hpp"

App::App() {
    this->scene = nullptr;
    this->showMessageBox = false;

    this->titleDimensions = MeasureTextEx(GetFontDefault(), "Raylib Tests", 32, 1);
}

void App::update(float dt) {
    if (this->scene != nullptr) {
        this->scene->update(dt);

        // TODO: implement scene changing
    }

    // otherwise do nothing
}

void App::draw() {
    if (this->scene != nullptr) {
        this->scene->draw();
        return;
    }

    // otherwise draw the menu
    ClearBackground(RAYWHITE);

    const float W = GetScreenWidth();
    const float H = GetScreenHeight();


    DrawText("Raylib Tests", (W - this->titleDimensions.x) / 2, (H - this->titleDimensions.y) * 0.1f, 32, BLACK);

    if (GuiButton((Rectangle) {100, 100, 150, 40}, "000 Frictionless Ball")) {
        this->scene = new SceneFrictionlessBall();
    }
}