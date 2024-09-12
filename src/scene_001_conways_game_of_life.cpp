

// #include "scene_001_conways_game_of_life.hpp"

// SceneConwaysGame::SceneConwaysGame() {
//     this->pause = false;
//     this->ball = {
//         .pos = { 0.5f, 0.5f},
//         .velocity = {
//             0.25f + ((float)(rand()) / (float)(RAND_MAX)) / 5,
//             0.1f + ((float)(rand()) / (float)(RAND_MAX)) / 5
//         },
//         .radius = 0.02f
//     };
// }

// SceneConwaysGame::~SceneConwaysGame() {
//     // do nothing
// }

// void SceneConwaysGame::on_enter() {
//     // do nothing
// }

// void SceneConwaysGame::on_exit() {
//     // do nothing
// }

// void SceneConwaysGame::update(float dt) {
//     if (IsKeyPressed(KEY_ESCAPE)) {
//         this->changeScene = true;
//         return;
//     }

//     const auto& currentState = this->useState1 ? &this->state1 : &this->state2;
//     const auto& nextState = this->useState1 ? &this->state2 : &this->state1;

//     for(int y = 0; y < size; ++y) {
//         for (int x = 0; x < size; ++x) {
//             int liveNeighbors = 0;
//             for (auto& n : NEIGHBORS) {
//                 const int nx = x + n.first;
//                 const int ny = y + n.second;

//                 if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
//                     liveNeighbors += (*currentState)[ny][nx];
//                 }
//             }

//             if ((*currentState)[y][x]) {
//                 (*nextState)[y][x] = (liveNeighbors == 2 || liveNeighbors == 3);
//             } else {
//                 (*nextState)[y][x] = (liveNeighbors == 3);
//             }
//         }
// }

// void SceneConwaysGame::draw() {
//     onst float W = (float) GetScreenWidth();
//         const float H = (float) GetScreenHeight();
        
//         // Draw the grid
//         ClearBackground(RAYWHITE);

//         const float start_x = W * START;
//         const float x_mod = (W*END - start_x) / (float) size;

//         const float start_y = H * START;
//         const float y_mod = (H*END - start_y) / (float) size;

//         const float mod = std::min(x_mod, y_mod);

//         float y_pos = H*START;
//         for(std::size_t y = 0; y < size; ++y, y_pos+=mod) {
//             float x_pos = W*START;
//             for(std::size_t x = 0; x < size; ++x, x_pos+=mod) {
//                 if ((*nextState)[y][x]) {
//                     DrawRectangle(x_pos, y_pos, mod-1, mod-1, BLACK);
//                 }
//             }
//         }

//         DrawText("Conway's Game of Life", start_x, start_y-30, 20, BLACK);

//         this->useState1 = !this->useState1;
// }