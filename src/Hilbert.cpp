#include "Hilbert.hpp"

Hilbert::Hilbert() {
    order = 1;
    N = pow(2, order);
    max_size = pow(N, 2);
    index = 1; // skip first, we know what it always is
    last_pos = HILBERT_POSITIONS[0];
}

Vector2 Hilbert::generate_next() {
    std::size_t i = index;
    std::size_t pos_index = i & 3;
    Vector2 pos = HILBERT_POSITIONS[pos_index];

    for (std::size_t j = 1; j < order; ++j) {
        i = i >> 2;
        pos_index = i & 3;
        const float length = pow(2, j);

        switch (pos_index) {
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
                printf("Unhandled index value: %zu\n", pos_index);
                exit(1);
                break;
            }
        }
    }

    ++index;

    return pos;
}

bool Hilbert::is_done() const {
    return index >= max_size;
}

void Hilbert::increase_order() {
    ++order;
    N = pow(2, order);
    max_size = pow(N, 2);
    index = 1; // skip first, we know what it always is
    last_pos = HILBERT_POSITIONS[0];
}