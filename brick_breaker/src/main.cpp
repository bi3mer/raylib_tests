#include <cstdio>
#include <cstdlib>
#include "raylib.h"

/////////////////////// Constants //////////////////////////////
const float MENU_INSTRUCTIONS_SWITCH_TIME = 0.5f;

const int TITLE_FONT_SIZE = 40;
const char* TITLE_MENU = "Brick Breaker";
const char* TITLE_LOST = "YOU LOST!";
const char* TITLE_WON = "WOW!! You won!!";

const char* INSTRUCTIONS_MENU = "Press SPACE to play";
const char* INSTRUCTIONS_LOST = "Press SPACE to play again";
const char* INSTRUCTIONS_WON = "Why would you keep playing?";
const int INSTRUCTIONS_FONT_SIZE = 22;

/////////////////////// Game State //////////////////////////////
enum Scene {
    MENU = 0,
    GAME,
    LOST,
    WON
};

typedef struct State {
    bool show_instructions;
    Scene current_scene;
    int lives;
    float time;
} State;

/////////////////////// Function Initializations /////////////////////// 
void init_state(State&); 
void initialize_state_for_game(State&); 

void menu_update(State&);
void menu_render(const State&);

void game_update(State&);
void game_render(const State&);

/////////////////////// Game Logic  /////////////////////// 
void update(State& state) {
    switch(state.current_scene) {
    case GAME:
        game_update(state);
        break;
    case MENU:
    case LOST:
    case WON:
        menu_update(state);
        break;
    default:
        printf("Unhandled scene type in update: %d\n", (int) state.current_scene);
        exit(1);
    }
}

void render(const State& state) {
    ClearBackground(BLACK);

    switch (state.current_scene) {
    case GAME:
        game_render(state);
        break;
    case MENU:
    case LOST:
    case WON:
        menu_render(state);
        break;
    default:
        printf("Unhandled scene type in render: %d\n", (int) state.current_scene);
        exit(1);
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
    InitWindow(1080, 720, "CFB: Snake");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    State state;
    init_state(state);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(wasm_step, &state, 0, 1);
#else
    while (!WindowShouldClose()) {
        bool is_menu_state = state.current_scene == MENU || state.current_scene == WON || state.current_scene == LOST;
        if (is_menu_state && IsKeyPressed(KEY_ESCAPE)) {
            break;
        }

        update(state);

        BeginDrawing();
        render(state);
        EndDrawing();
    }
#endif

    CloseWindow();
    return 0;
}


/////////////////////// Menu Functions //////////////////////////////
void init_state(State& state) {
    state.show_instructions = true;
    state.current_scene = Scene::MENU;
}

void initialize_state_for_game(State& state) {
    printf("initialize_state_for_game not yet implemented\n");
}

/////////////////////// Menu Functions //////////////////////////////
void menu_update(State& state) {
    if (IsKeyPressed(KEY_SPACE)) {
        state.current_scene = Scene::GAME;
        initialize_state_for_game(state);
        return;
    }

    state.time += GetFrameTime();
    if (state.time > MENU_INSTRUCTIONS_SWITCH_TIME) {
        state.time = 0;
        state.show_instructions = !state.show_instructions;
    } 
}

void menu_render(const State& state) {
    const float W = (float) GetScreenWidth();
    const float H = (float) GetScreenHeight();
    
    const char* title = TITLE_MENU;
    const char* instructions = INSTRUCTIONS_MENU;

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
        (W - titleDimensions.x) / 2, 
        (H - titleDimensions.y) * 0.1f, 
        TITLE_FONT_SIZE, 
        RAYWHITE
    );

    if (state.show_instructions) {
        DrawText(
            instructions, 
            (W - instructionDimensions.x) / 2, 
            (H - instructionDimensions.y) / 2, 
            INSTRUCTIONS_FONT_SIZE, 
            RAYWHITE
        );
    }
}

/////////////////////// Game Functions //////////////////////////////
void game_update(State& state) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        state.current_scene = Scene::MENU;
        return;
    }

    printf("game_update not yet implemented\n");
}

void game_render(const State& state) {
    printf("game_render not yet implmeented\n");
}
