#ifndef __SCENE_MENU_HPP__
#define __SCENE_MENU_HPP__

#include "scene.hpp"
#include "raylib.h"

class App {
public: 
    App();
    void update(float dt);
    void draw();
private:
    Scene* scene;
    bool showMessageBox;
    Vector2 titleDimensions;
};
#endif