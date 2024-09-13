#ifndef __APP_HPP__
#define __APP_HPP__

#include "raylib.h"
#include "raygui.hpp"

#include "IScene.hpp"
#include "SceneFrictionlessBall.hpp"
#include "SceneConwaysGameOfLife.hpp"
#include "SceneHilbertCurves.hpp"

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
    ISceneFactory* sceneFactories[3];
};
#endif