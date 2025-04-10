#include "raylib.h"
#include "ui.h"

void HandleInput(float *gain) {
    if (IsKeyPressed(KEY_UP)) {
        *gain *= 1.1f;
    } else if (IsKeyPressed(KEY_DOWN)) {
        *gain *= 0.9f;
    }
}
