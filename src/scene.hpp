#ifndef __SCENE_HPP__
#define __SCENE_HPP__

class IScene {
public:
    bool changeScene = false;

    virtual inline ~IScene() = default;

    virtual inline void on_enter() = 0;
    virtual inline void on_exit() = 0;
    virtual inline void update(float dt) = 0;
    virtual inline void draw() = 0;
};
#endif