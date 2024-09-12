#include "app.hpp"

App::App() {
    this->scene = nullptr;
    this->titleDimensions = MeasureTextEx(GetFontDefault(), "Raylib Tests", 32, 1);

    this->sceneFactories[0] = new SceneFactory<SceneFrictionlessBall>((char*) "Frictionless Ball");
    this->sceneFactories[1] = new SceneFactory<SceneConwaysGame>((char*) "Conway's Game of Life");
}

App::~App() {
    if (this->scene == nullptr) {
        delete this->scene;
    }

    for (ISceneFactory* sf : this->sceneFactories) {
        delete sf;
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
    for (const ISceneFactory* sf : this->sceneFactories) {
        if (GuiButton((Rectangle) {100, y, 150, 40}, sf->getName())) {
            this->scene = sf->constructScene();
        }
        
        y += 100; 
    }
}
