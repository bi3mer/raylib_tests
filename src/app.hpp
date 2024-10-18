#ifndef __APP_HPP__
#define __APP_HPP__

#include "raylib.h"
#include "raygui.hpp"

#include "IScene.hpp"

#include "ISceneFactory.hpp"

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
    ISceneFactory* simulationFactories[3];
    ISceneFactory* gameFactories[2];
};
#endif
