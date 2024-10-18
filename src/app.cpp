#include "app.hpp"
#include "ISceneFactory.hpp"
#include "SceneFrictionlessBall.hpp"
#include "SceneConwaysGameOfLife.hpp"
#include "SceneHilbertCurves.hpp"
#include "PongMenu.hpp"
#include "Snake.hpp"
#include "SceneFactory.hpp"
#include "raygui.hpp"
#include "raylib.h"

App::App() {
    isRunning = true;
    scene = nullptr;
    titleDimensions = MeasureTextEx(GetFontDefault(), "Raylib Tests", 32, 1);

    simulationFactories[0] = new SceneFactory<SceneFrictionlessBall>("Frictionless Ball");
    simulationFactories[1] = new SceneFactory<SceneConwaysGame>("Conway's Game of Life");
    simulationFactories[2] = new SceneFactory<SceneHilbertCurves>("Hilbert Curves");
    
    gameFactories[0] = new SceneFactory<PongMenu>("Pong");
    gameFactories[1] = new SceneFactory<Snake>("Snake");
}

App::~App() {
    if (scene == nullptr) {
        delete scene;
    }

    for (const ISceneFactory* sf : simulationFactories) {
        delete sf;
    }

    for (const ISceneFactory* gf : gameFactories) {
        delete gf;
    }
}

void App::update(float dt) {
    if (scene != nullptr) {
        scene->update(dt);

        if (scene->changeScene) {
            SetWindowTitle("Raylib Tests");
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

    float y = 200;
    for (const ISceneFactory* sf : simulationFactories) {
        if (GuiButton((Rectangle) {100, y, 150, 40}, sf->getName())) {
            SetWindowTitle(sf->getName());
            scene = sf->constructScene();
            scene->on_enter();
        }

        y += 100; 
    }


    y = 200;
    for (const ISceneFactory* sf : gameFactories) {
        if (GuiButton((Rectangle) {450, y, 150, 40}, sf->getName())) {
            SetWindowTitle(sf->getName());
            scene = sf->constructScene();
            scene->on_enter();
        }

        y += 100; 
    }
}
