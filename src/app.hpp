#ifndef __APP_HPP__
#define __APP_HPP__

#include "raylib.h"
#include "raygui.hpp"

#include "scene.hpp"
#include "scene_000_frictionless_ball.hpp"

#include "scene_type.hpp"

class App {
public: 
    App();
    ~App();
    void update(float);
    void draw();
    void set_scene(SceneType);
private:
    IScene* scene;
    Vector2 titleDimensions;
};
#endif