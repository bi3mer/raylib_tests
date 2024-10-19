#ifndef HILBERT_HPP
#define HILBERT_HPP

#include <cstddef>
#include <deque>
#include <raylib.h>
#include <raymath.h>

const Vector2 HILBERT_POSITIONS[] = {{0.0f, 0.0f},  {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

class Hilbert {
public:
    std::size_t N;
    
    Hilbert();
    Vector2 generate_next();
    bool is_done() const;
    void increase_order();
private:
    std::size_t order;
    std::size_t index;
    Vector2 last_pos;
    std::size_t max_size;
};
#endif