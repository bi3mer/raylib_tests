#include "menu.hpp"
#include "raylib.h"
#include <cstdio>

const int TITLE_FONT_SIZE = 40;
const char* TITLE_MENU = "Brick Breaker";
const char* TITLE_LOST = "YOU LOST!";
const char* TITLE_WON = "WOW!! You won!!";

const float MENU_INSTRUCTIONS_SWITCH_TIME = 0.5f;
const char* INSTRUCTIONS_MENU = "Press SPACE to play";
const char* INSTRUCTIONS_LOST = "Press SPACE to play again";
const char* INSTRUCTIONS_WON = "Why would you keep playing?";
const int INSTRUCTIONS_FONT_SIZE = 22;

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
