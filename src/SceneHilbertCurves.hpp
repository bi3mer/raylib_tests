#ifndef SCENE_HILBERT_CURVES_HPP
#define SCENE_HILBERT_CURVES_HPP

#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "Hilbert.hpp"
#include "IScene.hpp"

enum class HilbertState {
    HILBERT,
    PAUSE
};

class SceneHilbertCurves : public IScene {
public: 
    SceneHilbertCurves();
    ~SceneHilbertCurves();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();

private:
    HilbertState state;
    float time;
    Hilbert hilbert;
    std::vector<Vector2> points;
};
#endif