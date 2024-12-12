#include <algorithm>
#include <cstddef>
#include "cstdio"
#include "raylib.h"

#if __APPLE__
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#define GRID_SIZE 16
#define GRID_LENGTH GRID_SIZE*GRID_SIZE
#define SNAKE_MOVE_TIME 0.2

const int TITLE_FONT_SIZE = 40;
const char* TITLE_MENU = "SNAKE";
const char* TITLE_LOST = "YOU LOST!";
const char* TITLE_WON = "WOW!! You won!!";

const char* INSTRUCTIONS_MENU = "Press SPACE to play";
const char* INSTRUCTIONS_LOST = "Press SPACE to play again";
const char* INSTRUCTIONS_WON = "Why would you keep playing?";
const int INSTRUCTIONS_FONT_SIZE = 26;

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

/////////////////////// Useful Enums //////////////////////
enum Scene {
    MENU = 0,
    GAME,
    LOST,
    WON
};

enum CellType {
    EMPTY = 0,
    FOOD,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

/////////////////////// Convert 2d coords to 1d index ///////////////////////
typedef struct Position {
    int x;
    int y;
} Position;

inline std::size_t to_index(const std::size_t x, const std::size_t y) {
    return y * GRID_SIZE + x;
}

inline std::size_t to_index(const Position& pos) {
    return pos.y * GRID_SIZE + pos.x;
}

inline void position_from_direction(CellType dir, Position& pos_modifier) {
    switch(dir) {
        case NORTH:
            pos_modifier.x = 0;
            pos_modifier.y = -1;
            break;
        case EAST:
            pos_modifier.x = 1;
            pos_modifier.y = 0;
            break;
        case SOUTH:
            pos_modifier.x = 0;
            pos_modifier.y = 1;
            break;
        case WEST:
            pos_modifier.x = -1;
            pos_modifier.y = 0;
            break;
        default:
            printf("Only cardinal directions for snake directions: %d\n", (int) dir);
            exit(1);
    }
}

/////////////////////// Initial State Variables //////////////////////////////
typedef struct State {
    bool show_instructions;
    float time;
    Scene current_scene;
    CellType snake_direction; // only last four of cell type
    std::size_t snake_size;
    Position snake_head;
    Position snake_tail;
    Shader shader;
    RenderTexture2D renderTexture;
    CellType grid[GRID_SIZE * GRID_SIZE];
} State;

/////////////////////// Food Placement Helper //////////////////////////////
void place_food(State& state) {
    std::size_t index;
    if (state.snake_size <= GRID_LENGTH / 2) {
        // If the snake is samll, we are pretty much guaranteed to get an empty cell
        // first try.
        do {
            index = GetRandomValue(0, GRID_LENGTH-1);
        } while(state.grid[index] != EMPTY);
    } else {
        // otherwwise, it's pretty long, so we find the empty indexes first,
        // and we already know the length based on the size of the grid and the
        // the size of the snake
        std::size_t indices[GRID_LENGTH - state.snake_size];
        std::size_t size = 0;

        for(std::size_t i = 0; i < GRID_LENGTH; ++i) {
            if (state.grid[i] == CellType::EMPTY) {
                indices[size] = i;
                ++size;
            }
        }

        index = indices[GetRandomValue(0, size-1)];
    }

    state.grid[index] = FOOD;
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
        state.time = 0;
        for (std::size_t i = 0; i < GRID_LENGTH; ++i) {
            state.grid[i] = CellType::EMPTY;
        }

        state.snake_direction = CellType::EAST;
        state.snake_size = 1;

        const std::size_t mid_point = GRID_SIZE / 2;
        state.snake_head.x = mid_point;
        state.snake_head.y = mid_point;
        state.snake_tail.x = mid_point;
        state.snake_tail.y = mid_point;

        state.grid[to_index(state.snake_head)] = CellType::EAST; // snake starts going to the right
        place_food(state);
    }
}

void update_game(State& state) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        state.current_scene = Scene::MENU;
        return;
    }

    // update snake direction based on player input
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && state.snake_direction != SOUTH) {
        state.snake_direction = NORTH;
    } else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && state.snake_direction != WEST) {
        state.snake_direction = EAST;
    } else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && state.snake_direction != NORTH) {
        state.snake_direction = SOUTH;
    } else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && state.snake_direction != EAST) {
        state.snake_direction = WEST;
    }

    // if it is not time to move the snake, don't move the snake
    state.time += GetFrameTime();
    if (state.time < SNAKE_MOVE_TIME) {
        return; // nothing to be done
    }

    // it is time to move the snake
    state.time = 0;
    Position pos_modifier;
    position_from_direction(state.snake_direction, pos_modifier);

    // move the head
    state.grid[to_index(state.snake_head)] = state.snake_direction;
    state.snake_head.x += pos_modifier.x;
    state.snake_head.y += pos_modifier.y;

    // check for out of bounds
    if (state.snake_head.x < 0 || state.snake_head.x >= GRID_SIZE || state.snake_head.y < 0 || state.snake_head.y >= GRID_SIZE) {
        state.current_scene = Scene::LOST; // player lost
        return;
    }

    const std::size_t head_index = to_index(state.snake_head);

    switch (state.grid[head_index]) {
        case FOOD:
            ++state.snake_size; // taill isn't moved, so the snake grows in size

            if (state.snake_size == GRID_LENGTH) {
                state.current_scene = WON;
            } else {
                // place food
                place_food(state);
            }
            break;
        case NORTH:
        case EAST:
        case SOUTH:
        case WEST:
            // snake collided with itself, player lost
            state.current_scene = LOST;
            break;
        case EMPTY: {
            // move the tail
            const std::size_t tail_index = to_index(state.snake_tail);
            position_from_direction(state.grid[tail_index], pos_modifier);
            state.grid[tail_index] = EMPTY;
            state.snake_tail.x += pos_modifier.x;
            state.snake_tail.y += pos_modifier.y;
            break;
        }
        default:
            printf("Unhandled cell type: %d\n", (int) state.grid[head_index]);
            exit(1);
    }

    state.grid[head_index] = EAST; // dir replaced on next move
}

void update(State& state) {
    switch(state.current_scene) {
        case Scene::MENU:
        case Scene::WON:
        case Scene::LOST:
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
    const char* title;
    const char* instructions;

    switch(state.current_scene) {
        case MENU:
            title = TITLE_MENU;
            instructions = INSTRUCTIONS_MENU;
            break;
        case WON:
            title = TITLE_WON;
            instructions = INSTRUCTIONS_WON;
            break;
        case LOST:
            title = TITLE_LOST;
            instructions = INSTRUCTIONS_LOST;
            break;
        default:
            printf("Unhandled scene type in render_menu: %d\n", (int) state.current_scene);
            break;
    }

    Vector2 titleDimensions = MeasureTextEx(GetFontDefault(), title, TITLE_FONT_SIZE, 1);
    Vector2 instructionDimensions = MeasureTextEx(GetFontDefault(), instructions, INSTRUCTIONS_FONT_SIZE, 1);

    DrawText(
        title,
        (WINDOW_WIDTH - titleDimensions.x) / 2,
        (WINDOW_HEIGHT - titleDimensions.y) * 0.1f,
        TITLE_FONT_SIZE,
        RAYWHITE
    );

    if (state.show_instructions) {
        DrawText(
            instructions,
            (WINDOW_WIDTH - instructionDimensions.x) / 2,
            (WINDOW_HEIGHT - instructionDimensions.y) / 2,
            INSTRUCTIONS_FONT_SIZE,
            RAYWHITE
        );
    }
}

void render_game(const State& state) {
    const float grid_length = 0.8f * WINDOW_HEIGHT;

    float startX = (WINDOW_WIDTH - grid_length) / 2;
    float startY =  0.1f*WINDOW_HEIGHT;

    const float cell_dimension = grid_length / GRID_SIZE;

    for (std::size_t y = 0; y < GRID_SIZE; ++y) {
        const std::size_t col = y * GRID_SIZE;

        for (std::size_t x = 0; x < GRID_SIZE; ++x) {
            const int posX = startX + cell_dimension*x;
            const int posY = startY + cell_dimension*y;

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
                    break;
            }
        }
    }

    // draw border
    DrawRectangleLinesEx((Rectangle){startX, startY, grid_length, grid_length}, 2, RED);
}

void render(const State& state) {
    // render to texture
    BeginTextureMode(state.renderTexture);
    ClearBackground(BLACK);

    switch(state.current_scene) {
        case Scene::MENU:
        case Scene::WON:
        case Scene::LOST:
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

    EndTextureMode();

    // get scale
    const float screenWidth = GetScreenWidth();
    const float screenHeight = GetScreenHeight();
    const float scale = std::min(screenWidth/WINDOW_WIDTH, screenHeight/WINDOW_HEIGHT);

    // draw texture scaled to current window size
    BeginDrawing();
        BeginShaderMode(state.shader);
            ClearBackground(BLACK);

            DrawTexturePro(
                state.renderTexture.texture,
                (Rectangle) {
                    0,
                    0,
                    (float) WINDOW_WIDTH,
                    -(float) WINDOW_HEIGHT
                },
                (Rectangle) {
                    (GetScreenWidth() - ((float)WINDOW_WIDTH*scale))*0.5f,
                    (GetScreenHeight() - ((float)WINDOW_HEIGHT*scale))*0.5f,
                    (float) WINDOW_WIDTH * scale,
                    (float) WINDOW_HEIGHT * scale
                },
                (Vector2){ 0, 0 },
                0.0f,
                WHITE
            );

        EndShaderMode();
    EndDrawing();
}

/////////////////////// WASM or Desktop Logic  ///////////////////////
#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>

    void wasm_step(void* void_state) {
        State* state = static_cast<State*>(void_state);

        update(*state);
        render(*state);
    }
#endif

int main() {
    // --------- Init
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CFB: Snake");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    State state;
    state.show_instructions = true;
    state.time = 0;
    state.current_scene = Scene::MENU;
    state.shader = LoadShader(0, TextFormat("resources/%i/crt.fs", GLSL_VERSION));
    state.renderTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    // --------- Loop
#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &state, 0, 1);
#else
    while (!WindowShouldClose()) {
        bool is_menu_state = state.current_scene == MENU || state.current_scene == WON || state.current_scene == LOST;
        if (is_menu_state && IsKeyPressed(KEY_ESCAPE)) {
            break;
        }

        update(state);
        render(state);
    }
#endif

    // --------- De-Init
    UnloadShader(state.shader);
    UnloadRenderTexture(state.renderTexture);
    CloseWindow();

    return 0;
}
