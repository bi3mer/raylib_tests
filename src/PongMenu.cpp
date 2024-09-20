#include "PongMenu.hpp"

PongMenu::PongMenu() {
    runningGame = false;
    instructionsBlinkTime = 0;
    showInstructions = true;

    titleDimensions = MeasureTextEx(GetFontDefault(), title, titleSize, 1);
    instructionDimensions = MeasureTextEx(GetFontDefault(), instructions, instructionSize, 1);
}

PongMenu::~PongMenu() {}

void PongMenu::on_enter() { }
void PongMenu::on_exit() { }

void PongMenu::update(float dt) {
    if (runningGame) {
        game.update(dt);

        if (game.changeScene) {
            game.on_exit();
            runningGame = false;
        }
    } else {
        instructionsBlinkTime += dt;
        if (instructionsBlinkTime > 0.5f) {
            instructionsBlinkTime = 0.0f;
            showInstructions = !showInstructions;
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            changeScene = true;
        } else if (IsKeyPressed(KEY_SPACE)) {
            runningGame = true;
            
            game.on_enter();
            game.update(dt);

            // make sure instructions show on first frame when the user comes
            // back to the pong menu
            showInstructions = true;
            instructionsBlinkTime = 0;
        }
    }
}

void PongMenu::draw() {
    if (runningGame) {
        game.draw();
        return;
    }

    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    ClearBackground(RAYWHITE);

    DrawText(
        title, 
        (W - titleDimensions.x) / 2, 
        (H - titleDimensions.y) * 0.1f, 
        titleSize, 
        BLACK
    );

    if (showInstructions) {
        DrawText(
            instructions, 
            (W - instructionDimensions.x) / 2, 
            (H - instructionDimensions.y) / 2, 
            instructionSize, 
            BLACK
        );
    }

}