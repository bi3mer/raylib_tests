#ifndef __SCENE_MENU_HPP__
#define __SCENE_MENU_HPP__

#include "scene.hpp"

class SceneMenu : public Scene {
public: 
    void draw();
    Scene* change_scene();

private:
    bool showMessageBox = false;
};
#endif