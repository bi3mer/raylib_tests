#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <cstddef>
#include <random>

const std::pair<int, int> NEIGHBORS[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

template <std::size_t N>
class Conway {
public:
    Conway() {
        // create random matrix for Conway's game of life
        std::default_random_engine generator;
        generator.seed(time(NULL));
        std::uniform_real_distribution<float> distribution(0.0, 1.0);

        for (std::size_t y = 0; y < N; ++y) {
            for (std::size_t x = 0; x < N; ++x) {
                curState[y][x] = distribution(generator) >= 0.5f;
            }
        }
    };

    void step() {
        for(int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                int liveNeighbors = 0;
                for (auto& n : NEIGHBORS) {
                    const int nx = x + n.first;
                    const int ny = y + n.second;

                    if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                        liveNeighbors += curState[ny][nx];
                    }
                }

                if (curState[y][x]) {
                    nextState[y][x] = (liveNeighbors == 2 || liveNeighbors == 3);
                } else {
                    nextState[y][x] = (liveNeighbors == 3);
                }
            }
        }

        std::swap(curState, nextState);
    };

    const bool cellIsActive(const std::size_t row, const std::size_t col) const {
        return curState[row][col];
    };

private:
    bool curState[N][N];
    bool nextState[N][N];
};

#endif