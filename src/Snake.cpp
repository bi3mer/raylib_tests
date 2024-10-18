#include "Snake.hpp"
#include "raylib.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

/////////////////////// Convert 2d coords to 1d index ///////////////////////
inline std::size_t to_index(const Vector2SizeT& v) {
    return v.y * GRID_SIZE + v.x;
}

inline std::size_t to_index(const std::size_t x, const std::size_t y) {
    return y * GRID_SIZE + x;
}
/////////////////////////////////////////////////////////////////////////////

Snake::Snake() {}
Snake::~Snake() {}

void Snake::on_enter() {
    // initalize the grid
    for (std::size_t i = 0; i < GRID_SIZE*GRID_SIZE; ++i) {
        grid[i] = CellType::EMPTY;
    }

    // initalize snake position and place a food in the gri
    snake_head.x = floor(GRID_SIZE / 2);
    snake_head.y = floor(GRID_SIZE / 2);
    grid[to_index(snake_head)] = CellType::SNAKE;
}
void Snake::on_exit() {}

void Snake::update(float dt) {
    if (IsKeyDown(KEY_ESCAPE)) {
        changeScene = true;
        return;
    }
}

void Snake::draw() {
    ClearBackground(RAYWHITE);

    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    const float startX = W * 0.1f;
    const float startY = H * 0.1f;

    const float cell_width = (W * 0.8f) / (float) GRID_SIZE;
    const float cell_height = (H * 0.8f) / (float) GRID_SIZE;

    // draw the game grid
    for (std::size_t y = 0; y < GRID_SIZE; ++y) {
        const std::size_t col = y * GRID_SIZE;

        for (std::size_t x = 0; x < GRID_SIZE; ++x) {
            const std::size_t index = col + x;
            const float xPos = x * cell_width;
            const float yPos = y * cell_height;

            Color c;
            switch (grid[index]) {
            case CellType::EMPTY:
                continue; // nothing to draw
            case CellType::FOOD:
                printf("food\n");
                c = GREEN;
                break;
            case CellType::SNAKE:
                c = GRAY;
                break;
            default:
                printf("Unhandled grid type: %i\n", grid[index]);
                printf("Test: %i\n", CellType::SNAKE);
                exit(1);
            }

            DrawRectangle(startX + xPos, startY + yPos, cell_width - 1, cell_height - 1, c);
        }
    }

    // draw outline around the grid
    DrawRectangle(0, 0, W, startY, BLACK);
    DrawRectangle(0, H - startY + 1, W, startY, BLACK);
    DrawRectangle(0, 0, startX - 1, H, BLACK);
    DrawRectangle(W - startX + 1, 0, startX, H, BLACK);
}
