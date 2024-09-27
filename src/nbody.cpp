#include "nbody.hpp"

NBody::NBody() {}
NBody::~NBody() {}

void NBody::on_enter() {}
void NBody::on_exit() {}

void NBody::update(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        changeScene = true;
    }
}

void NBody::draw() {
    ClearBackground(RAYWHITE);
    DrawText("Not implemented yet...", GetScreenWidth() / 2, GetScreenHeight() / 2, 40, BLACK);
}