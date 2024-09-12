#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <cstddef>
#include <random>

const std::pair<int, int> NEIGHBORS[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

template <std::size_t size>
class Conway {
public:
    Conway() {
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
    };

    void step() {
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

        this->useState1 = !useState1;
    };

    const bool*** getBoard() const {
        return this->useState1 ? &this->state1 : &this->state2;
    };

private:
    bool state1[size][size];
    bool state2[size][size];
    bool useState1;
};

#endif