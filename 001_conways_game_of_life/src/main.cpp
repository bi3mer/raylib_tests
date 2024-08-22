#include <stdio.h>
#include <cstdint>
#include <algorithm>

#include "raylib.h"
#include "Simulation.hpp"

#define SIZE 100

#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    
    void wasm_step(void* voidState) {
        static_cast<Simulation<SIZE>*>(voidState)->step();
    }
#endif

int main(void) {
    Simulation<SIZE> simulation;

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &simulation, 0, 1);
#else
    while (!WindowShouldClose()) {
        simulation.step();
    }
#endif

    CloseWindow();

    return 0;
}