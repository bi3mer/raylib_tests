#ifndef HILBERT_HPP
#define HILBERT_HPP

#include <cstddef>
#include <deque>
#include <raylib.h>
#include <raymath.h>

const Vector2 POSITIONS[] = {{0.0f, 0.0f},  {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

class Hilbert {
public:
    std::size_t N;

    Hilbert(size_t order) {
        this->order = order;
        this->N = pow(2, order);
        this->max_size = pow(this->N, 2);
        this->index = 1; // skip first, we know what it always is
        this->last_pos = POSITIONS[0];
    }

    Vector2 generate_next() {
        std::size_t i = this->index;
        std::size_t index = i & 3;
        Vector2 pos = POSITIONS[index];

        for (std::size_t j = 1; j < this->order; ++j) {
            i = i >> 2;
            index = i & 3;
            const float length = pow(2, j);

            switch (index) {
                case 0: {
                    const float temp = pos.x;
                    pos.x = pos.y;
                    pos.y = temp;
                    break;
                }
                case 1: {
                    pos.y += length;
                    break;
                }
                case 2: {
                    pos.x += length;
                    pos.y += length;
                    break;
                }
                case 3: {
                    const float temp = length - 1.0f - pos.x;
                    pos.x = length - 1.0f - pos.y;
                    pos.y = temp;
                    pos.x += length; // TODO: come back to this
                    break;
                }
                default: {
                    printf("Unhandled index value: %zu\n", index);
                    exit(1);
                    break;
                }
            }
        }

        ++this->index;

        return pos;
    }
    
    bool is_done() {
        return this->index >= this->max_size;
    }
    
    void increase_order() {
        ++this->order;
        this->N = pow(2, order);
        this->max_size = pow(this->N, 2);
        this->index = 1; // skip first, we know what it always is
        this->last_pos = POSITIONS[0];
    }
private:
    std::size_t order;
    std::size_t index;
    Vector2 last_pos;
    std::size_t max_size;
};
#endif