#include "SceneConwaysGameOfLife.hpp"

SceneConwaysGame::SceneConwaysGame() {
    time = 0;
 }

SceneConwaysGame::~SceneConwaysGame() {
    // do nothing
}

void SceneConwaysGame::on_enter() { }

void SceneConwaysGame::on_exit() { }

void SceneConwaysGame::update(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        this->changeScene = true;
        return;
    }
    
    time += dt;
    if (time > 0.075f) {
        time = 0;
        this->conway.step();
    }
}

void SceneConwaysGame::draw() {
    const float W = (float) GetScreenWidth();
    const float H = (float) GetScreenHeight();
    
    // Draw the grid
    ClearBackground(RAYWHITE);

    const float start_x = W * 0.1f;
    const float x_mod = (W*0.9f - start_x) / 100.0f;

    const float start_y = H * 0.1f;
    const float y_mod = (H*0.9f - start_y) / 100.0f;

    const float mod = std::min(x_mod, y_mod);

    float y_pos = H*0.1f;
    for(std::size_t y = 0; y < 100; ++y, y_pos+=mod) {
        float x_pos = W*0.1;
        for(std::size_t x = 0; x < 100; ++x, x_pos+=mod) {
            if (this->conway.cellIsActive(y, x)) {
                DrawRectangle(x_pos, y_pos, mod-1, mod-1, BLACK);
            }
        }
    }

    DrawText("Conway's Game of Life", start_x, start_y-30, 20, BLACK);
}