#include "PongMenu.hpp"

PongMenu::PongMenu() {
    instructionsBlinkTime = 0;
    showInstructions = true;

    titleDimensions = MeasureTextEx(GetFontDefault(), title, titleSize, 1);
    instructionDimensions = MeasureTextEx(GetFontDefault(), instructions, instructionSize, 1);
}

PongMenu::~PongMenu() {}

void PongMenu::on_enter() { }
void PongMenu::on_exit() {
    changeScene = false;
}

void PongMenu::update(float dt) {
    instructionsBlinkTime += dt;

    if (instructionsBlinkTime > 0.5f) {
        instructionsBlinkTime = 0.0f;
        showInstructions = !showInstructions;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        changeScene = true;
    
        // make sure instructions show on first frame when the user comes
        // back to the pong menu
        showInstructions = true;
        instructionsBlinkTime = 0;
    }
}

void PongMenu::draw() {
    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    ClearBackground(BLACK);

    DrawText(
        title, 
        (W - titleDimensions.x) / 2, 
        (H - titleDimensions.y) * 0.1f, 
        titleSize, 
        WHITE
    );

    if (showInstructions) {
        DrawText(
            instructions, 
            (W - instructionDimensions.x) / 2, 
            (H - instructionDimensions.y) / 2, 
            instructionSize, 
            WHITE
        );
    }

}
