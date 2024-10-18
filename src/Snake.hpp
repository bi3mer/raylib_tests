#ifndef SNAKE_HPP
#define SNAKE_HPP
#include "IScene.hpp"
#include "Vector2SizeT.hpp"
#include "raylib.h"

#define GRID_SIZE 20
#define MOVE_TIME 0.3


/**
 * [ ] Food placement procedure
 * [ ] Better display of the grid
 * [ ] Snake moves every X seconds 
 * [ ] Snake can change directions
 * [ ] Snake increase in size on collision with food
 * [ ] Snake loses when head goes outside of grid
 * [ ] Snake loses when head touches part of the body
 * [ ] Player lost screen
 * [ ] Player can restart on loss
 * [ ] Snake can win
 * [ ] Player won screen
 */

class Snake : public IScene {
public:
    Snake();
    ~Snake();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();

private:
    void fill_foid();

    enum CellType {
        EMPTY = 0,
        FOOD,
        SNAKE
    };
    
    enum Direction {
        North = 0,
        EAST,
        SOUTH,
        WEST
    };

    CellType grid[GRID_SIZE * GRID_SIZE];
    Direction snake_direction;
    Vector2SizeT snake_head;
    Vector2SizeT snake_tail;
};
#endif
