#ifndef HILBERT_HPP
#define HILBERT_HPP

#include <cstddef>
#include <deque>
#include <raylib.h>
#include <raymath.h>

const Vector2 POSITIONS[] = {{0.1f, 0.1f},  {0.1f, 0.9f}, {0.9f, 0.9f}, {0.9f, 0.1f}};

class Hilbert {
public:
    Hilbert(size_t order) {
        this->order = order;
        this->max_size = pow(pow(2, order), 2);
        this->index = 1; // skip first, we know what it always is
        this->last_pos = POSITIONS[0];
    }

    Vector2 generate_next() {
        std::size_t i = this->index;
        std::size_t index = i & 3;
        Vector2 pos = POSITIONS[index];

        for (std::size_t j = 1; j < this->order; ++j) {
            i = i << 2;
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
                    pos.x += length;
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

    // void generate_and_draw(std::size_t count) {
    //     for(; this->index < count && this->index < this->max_size; ++this->index) {
    //         std::size_t i = this->index;
    //         std::size_t index = this->index & 3;
    //         Vector2 pos = POSITIONS[index];

    //         for (std::size_t j = 0; j < this->order; ++j) {
    //             i = i << 2;
    //             index = i & 3;
    //             const float length = pow(2, j);

    //             switch (index) {
    //                 case 1: {
    //                     const float temp = pos.x;
    //                     pos.x = pos.y;
    //                     pos.y = temp;
    //                     break;
    //                 }
    //                 case 2: {
    //                     pos.y += length;
    //                     break;
    //                 }
    //                 case 3: {
    //                     pos.x += length;
    //                     pos.y += length;
    //                     break;
    //                 }
    //                 case 4: {
    //                     const float temp = length - 1.0f - pos.x;
    //                     pos.x = length - 1.0f - pos.y;
    //                     pos.y = temp;
    //                     pos.x += length;
    //                     break;
    //                 }
    //                 default: {
    //                     printf("Unhandled index value: %zu\n", index);
    //                     exit(1);
    //                     break;
    //                 }
    //             }
    //         }

    //         // draw with pos
    //         DrawLine(last_pos.x, last_pos.y, pos.x, pos.y, RED);
    //         last_pos = pos;
    //     }
    // }
    
    bool is_done() {
        return this->index >= this->max_size;
    }
private:
    std::size_t order;
    std::size_t index;
    std::size_t max_size;
    Vector2 last_pos;
};
#endif