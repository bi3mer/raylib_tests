#ifndef __SCENE_TYPE_HPP__
#define __SCENE_TYPE_HPP__

#include <string>
#include <stdio.h>

#include "scene_000_frictionless_ball.hpp"

enum SceneType {
    FRICTIONLESS_BALL = 0,
    CONWAYS_GAME_OF_LIFE,
    HILBERT_CURVE,
    LAST
};

const char* sceneTypeToString(SceneType scene);
IScene* sceneTypeToScene(SceneType scene);

#endif