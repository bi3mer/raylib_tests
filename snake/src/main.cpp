#include <algorithm>
#include <cstddef>
#include "raylib.h"

/**
 * [ ] Food placement procedure.
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

#define GRID_SIZE 20
#define GRID_LENGTH GRID_SIZE*GRID_SIZE
#define MOVE_TIME 0.3
#define COLOR_EMPTY  (Color){ 120, 120, 120, 80 }

const int TITLE_FONT_SIZE = 40;
const char* TITLE = "SNAKE";

const char* INSTRUCTIONS = "Press SPACE to play";
const int INSTRUCTIONS_FONT_SIZE = 22;

/////////////////////// Convert 2d coords to 1d index ///////////////////////
typedef struct Position {
    std::size_t x;
    std::size_t y;
} Position;

inline std::size_t to_index(const std::size_t x, const std::size_t y) {
    return y * GRID_SIZE + x;
}

inline std::size_t to_index(const Position& pos) {
    return pos.y * GRID_SIZE + pos.x;
}

/////////////////////// Initial State Variables //////////////////////////////

enum Scene {
    MENU = 0,
    GAME
};

enum CellType {
    EMPTY = 0,
    FOOD,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct State {
    bool show_instructions;
    float time;
    Scene current_scene;
    CellType snake_direction; // only last four of cell type
    Position snake_head;
    Position snake_tail;
    CellType grid[GRID_SIZE * GRID_SIZE];
} State;

void init_state(State& state) {
    state.show_instructions = true;
    state.time = 0;
    state.current_scene = Scene::MENU;
}

/////////////////////// Update Logic  ///////////////////////
void update_menu(State& state) {
    state.time += GetFrameTime();
    if (state.time > 0.5f) {
        state.time = 0;
        state.show_instructions = !state.show_instructions;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        state.current_scene = Scene::GAME;

        // set up for the snake game
        for (std::size_t i = 0; i < GRID_LENGTH; ++i) {
            state.grid[i] = CellType::EMPTY;
        }

        state.snake_direction = CellType::EAST;

        const std::size_t mid_point = GRID_SIZE / 2;
        state.snake_head.x = mid_point;
        state.snake_head.y = mid_point;
        state.snake_tail.x = mid_point;
        state.snake_tail.y = mid_point;

        state.grid[to_index(state.snake_head)] = CellType::EAST; // snake starts going to the right
        state.grid[to_index(GRID_SIZE - 3, mid_point)] = CellType::FOOD; // first food is deterministic
    }
}

void update_game(State& state) {

}

void update(State& state) {
    switch(state.current_scene) {
        case Scene::MENU: 
            update_menu(state);
            break;
        case Scene::GAME: 
            update_game(state);
            break;
        
        default: 
            printf("Unhandled scene type in update: %d\n", (int) state.current_scene);
            exit(1);
            break;
    }
}

/////////////////////// Render Logic  ///////////////////////
void render_menu(const State& state) {
    const float W = (float) GetScreenWidth();
    const float H = (float) GetScreenHeight();
 
    Vector2 titleDimensions = MeasureTextEx(GetFontDefault(), TITLE, TITLE_FONT_SIZE, 1);
    Vector2 instructionDimensions = MeasureTextEx(GetFontDefault(), INSTRUCTIONS, INSTRUCTIONS_FONT_SIZE, 1);   

    DrawText(
        TITLE, 
        (W - titleDimensions.x) / 2, 
        (H - titleDimensions.y) * 0.1f, 
        TITLE_FONT_SIZE, 
        WHITE
    );

    if (state.show_instructions) {
        DrawText(
            INSTRUCTIONS, 
            (W - instructionDimensions.x) / 2, 
            (H - instructionDimensions.y) / 2, 
            INSTRUCTIONS_FONT_SIZE, 
            WHITE
        );
    }
}

void render_game(const State& state) {
    const float W = (float) GetScreenWidth();
    const float H = (float) GetScreenHeight();

    const float min = std::min(H, W); 

    const float start = 0.1f*min;
    /*const float end = 0.9f*min;*/
    const float cell_dimension = 0.8f*min / GRID_SIZE;

    for (std::size_t y = 0; y < GRID_SIZE; ++y) {
        const std::size_t col = y * GRID_SIZE;

        for (std::size_t x = 0; x < GRID_SIZE; ++x) {
            const int posX = start + cell_dimension*x;
            const int posY = start + cell_dimension*y;

            switch(state.grid[col + x]) {
                case FOOD:
                    DrawRectangle(posX, posY, cell_dimension - 1, cell_dimension - 1, GREEN);
                    break;
                case NORTH: 
                case EAST:
                case SOUTH:
                case WEST:
                    DrawRectangle(posX, posY, cell_dimension - 1, cell_dimension - 1, RED);
                    break;
                default:
                    DrawRectangle(posX, posY, cell_dimension - 1, cell_dimension - 1, COLOR_EMPTY);
                    break;
            }
        }
    }


}

void render(const State& state) {
    ClearBackground(BLACK);

    switch(state.current_scene) {
        case Scene::MENU: 
            render_menu(state);
            break;
        case Scene::GAME: 
            render_game(state);
            break;
        
        default: 
            printf("Unhandled scene type in update: %d\n", (int) state.current_scene);
            exit(1);
            break;
    }
}

/////////////////////// WASM or Desktop Logic  ///////////////////////
#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    
    void wasm_step(void* void_state) {
        State* state = static_cast<State*>(void_state);

        update(*state);

        BeginDrawing();
        render(*state);
        EndDrawing();
    }
#endif

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "CFB: Frictionless Ball");
    SetTargetFPS(60);

    State state;
    init_state(state);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &state, 0, 1);
#else
    while (!WindowShouldClose()) {
        update(state);

        BeginDrawing();
        render(state);
        EndDrawing();
    }
#endif

    CloseWindow();
    return 0;
}
