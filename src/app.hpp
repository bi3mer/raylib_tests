#ifndef __APP_HPP__
#define __APP_HPP__

#include "raylib.h"
#include "raygui.hpp"

#include "scene.hpp"
#include "scene_000_frictionless_ball.hpp"
#include "scene_001_conways_game_of_life.hpp"

#include "ISceneFactory.hpp"
#include "SceneFactory.hpp"

class App {
public: 
    bool isRunning;
    
    App();
    ~App();
    void update(float);
    void draw();
private:
    IScene* scene;
    Vector2 titleDimensions;
    ISceneFactory* sceneFactories[2];
};
#endif