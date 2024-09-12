#include "scene_type.hpp"

const char* sceneTypeToString(SceneType scene) {
    switch (scene) {
        case SceneType::FRICTIONLESS_BALL: 
            return "Frictionless Ball";
        case SceneType::CONWAYS_GAME_OF_LIFE:
            return "Conway's Game of Life";
        case SceneType::HILBERT_CURVE:
            return "Hilbert Curve";
        default:
            printf("Error: unhandled scene type: %d", scene);
            exit(1);    
    }
}

IScene* sceneTypeToScene(SceneType scene) {
    switch (scene) {
        case SceneType::FRICTIONLESS_BALL: 
            return new SceneFrictionlessBall();
        case SceneType::CONWAYS_GAME_OF_LIFE:
        case SceneType::HILBERT_CURVE:
        default:
            printf("Error: unhandled scene type: %d", scene);
            exit(1);    
    }
}