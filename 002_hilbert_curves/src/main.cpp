#include <stdio.h>
#include <cstdint>
#include <algorithm>

#include "raylib.h"
#include "Hilbert.hpp"


#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    
    void wasm_step(void* voidState) {
        static_cast<Simulation<SIZE>*>(voidState)->step();
    }
#endif

int main(void) {
    Hilbert hilbert(2);
    printf("0:\t%f, %f\n", POSITIONS[0].x, POSITIONS[0].y);

    std::size_t index = 1;
    while(!hilbert.is_done()) {
        Vector2 pos = hilbert.generate_next();
        printf("%zu:\t%f, %f\n", index, pos.x, pos.y);

        ++index;
    }

    return 0;
}