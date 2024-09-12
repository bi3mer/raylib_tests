#include "app.hpp"

App::App() {
    this->scene = nullptr;
    this->titleDimensions = MeasureTextEx(GetFontDefault(), "Raylib Tests", 32, 1);
}

App::~App() {
    if (this->scene == nullptr) {
        delete this->scene;
    }
}

void App::update(float dt) {
    if (this->scene != nullptr) {
        this->scene->update(dt);

        if (this->scene->changeScene) {
            this->scene->on_exit();
            delete this->scene;
            this->scene = nullptr;
        }
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
    
    float y = 100;
    for (int s = SceneType::FRICTIONLESS_BALL; s < SceneType::LAST; ++s) {
        SceneType scene = (SceneType) s;
        if (GuiButton((Rectangle) {100, y, 150, 40}, sceneTypeToString(scene))) {
            this->scene = sceneTypeToScene(scene);
        }
        y += 100;
    }
}

void App::set_scene(SceneType scene) {
    #if DEBUG
    assert(scene != nullptr);
    #endif

}