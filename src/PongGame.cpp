#include "PongGame.hpp"

PongGame::PongGame() {

}

PongGame::~PongGame() {
    
}

void PongGame::on_enter() {

}

void PongGame::on_exit() {
    changeScene = false;
}

void PongGame::update(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        changeScene = true;
    }
    
}

void PongGame::draw() {
    ClearBackground(RAYWHITE);
    
}