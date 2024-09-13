#ifndef SCENE_CONWAYS_GAME_OF_LIFE_HPP
#define SCENE_CONWAYS_GAME_OF_LIFE_HPP

#include <algorithm>
#include "raylib.h"
#include "raymath.h"

#include "IScene.hpp"
#include "Conway.hpp"

class SceneConwaysGame : public IScene {
public: 
    SceneConwaysGame();
    ~SceneConwaysGame();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();

private:
    Conway<100> conway;
    float time;
};
#endif