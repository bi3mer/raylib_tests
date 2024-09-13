#include "SceneHilbertCurves.hpp"

SceneHilbertCurves::SceneHilbertCurves() {
    time = 0.0f;
    state = HilbertState::HILBERT;
    points.push_back(HILBERT_POSITIONS[0]);
}

SceneHilbertCurves::~SceneHilbertCurves() { }
void SceneHilbertCurves::on_enter() { }
void SceneHilbertCurves::on_exit() { }

void SceneHilbertCurves::update(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        this->changeScene = true;
        return;
    }

    switch(state) {
        case HilbertState::HILBERT: {
            if(hilbert.is_done()) {
                state = HilbertState::PAUSE;
            } else {
                points.push_back(hilbert.generate_next());
            }

            break;
        }
        case HilbertState::PAUSE: {
            time += dt;
            if (time > 1.0f) {
                time = 0.0f;
                state = HilbertState::HILBERT;
                hilbert.increase_order();

                points.clear();
                points.push_back(HILBERT_POSITIONS[0]);
            } 

            break;
        }
        default: {
            printf("Unhandled state type: %i\n", state);
            exit(1);
        }
    }
}

void SceneHilbertCurves::draw() {
    ClearBackground(RAYWHITE);

    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    const float x_length = W / (float) hilbert.N;
    const float y_length = H / (float) hilbert.N;

    Vector2 p = points[0];
    Vector2 last_point = {
        p.x * x_length + x_length / 2.0f,
        p.y * y_length + y_length / 2.0f
    };

    for (std::size_t i = 1; i < points.size(); ++i) {
        p = points[i];
        const float x = p.x * x_length + x_length/2.0f;
        const float y = p.y * y_length + y_length/2.0f;

        DrawLineEx({x ,y}, last_point, 2, RED);

        last_point.x = x;
        last_point.y = y;
    }
}
