#include "app.hpp"

App::App() {
    isRunning = true;
    scene = nullptr;
    titleDimensions = MeasureTextEx(GetFontDefault(), "Raylib Tests", 32, 1);

    sceneFactories[0] = new SceneFactory<SceneFrictionlessBall>((char*) "Frictionless Ball");
    sceneFactories[1] = new SceneFactory<SceneConwaysGame>((char*) "Conway's Game of Life");
    sceneFactories[2] = new SceneFactory<SceneHilbertCurves>((char*) "Hilbert Curves");
}

App::~App() {
    if (scene == nullptr) {
        delete scene;
    }

    for (const ISceneFactory* sf : sceneFactories) {
        delete sf;
    }
}

void App::update(float dt) {
    if (scene != nullptr) {
        scene->update(dt);

        if (scene->changeScene) {
            scene->on_exit();
            delete scene;
            scene = nullptr;
        }
    } else if (IsKeyPressed(KEY_ESCAPE)) {
        isRunning = false;
    }
}

void App::draw() {
    if (scene != nullptr) {
        scene->draw();
        return;
    }

    // otherwise draw the menu
    ClearBackground(RAYWHITE);

    const float W = GetScreenWidth();
    const float H = GetScreenHeight();


    DrawText("Raylib Tests", (W - titleDimensions.x) / 2, (H - titleDimensions.y) * 0.1f, 32, BLACK);
    
    float y = 100;
    for (const ISceneFactory* sf : sceneFactories) {
        if (GuiButton((Rectangle) {100, y, 150, 40}, sf->getName())) {
            scene = sf->constructScene();
        }
        
        y += 100; 
    }
}
