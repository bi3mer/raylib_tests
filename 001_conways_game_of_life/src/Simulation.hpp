#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <cstddef>
#include <random>

#include "raylib.h"

#define START 0.1f
#define END 0.9f

const std::pair<int, int> NEIGHBORS[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};


template <std::size_t size>
class Simulation {
public:
    Simulation() {
        // Set up raylib window
        SetTargetFPS(12);
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(720, 720, "Conway's Game of Life");

        // create random matrix for Conway's game of life
        std::default_random_engine generator;
        generator.seed(time(NULL));
        std::uniform_real_distribution<float> distribution(0.0, 1.0);

        for (std::size_t y = 0; y < size; ++y) {
            for (std::size_t x = 0; x < size; ++x) {
                this->state1[y][x] = distribution(generator) >= 0.5f;
            }
        }

        // simple class variables
        this->useState1 = true;
    }

    void step() {
        // Simulate step
        const auto& currentState = this->useState1 ? &this->state1 : &this->state2;
        const auto& nextState = this->useState1 ? &this->state2 : &this->state1;

        for(int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                int liveNeighbors = 0;
                for (auto& n : NEIGHBORS) {
                    const int nx = x + n.first;
                    const int ny = y + n.second;

                    if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
                        liveNeighbors += (*currentState)[ny][nx];
                    }
                }

                if ((*currentState)[y][x]) {
                    (*nextState)[y][x] = (liveNeighbors == 2 || liveNeighbors == 3);
                } else {
                    (*nextState)[y][x] = (liveNeighbors == 3);
                }
            }
        }

        // constants for the frame
        const float W = (float) GetScreenWidth();
        const float H = (float) GetScreenHeight();
        
        // Draw the grid
        BeginDrawing();
        ClearBackground(RAYWHITE);


        const float start_x = W * START;
        const float x_mod = (W*END - start_x) / (float) size;

        const float start_y = H * START;
        const float y_mod = (H*END - start_y) / (float) size;

        const float mod = std::min(x_mod, y_mod);

        float y_pos = H*START;
        for(std::size_t y = 0; y < size; ++y, y_pos+=mod) {
            float x_pos = W*START;
            for(std::size_t x = 0; x < size; ++x, x_pos+=mod) {
                if ((*nextState)[y][x]) {
                    DrawRectangle(x_pos, y_pos, mod-1, mod-1, BLACK);
                }
            }
        }

        DrawText("Conway's Game of Life", start_x, start_y-30, 20, BLACK);
        EndDrawing();

        this->useState1 = !this->useState1;
    }

private:
    bool state1[size][size];
    bool state2[size][size];
    bool useState1;
};

#endif