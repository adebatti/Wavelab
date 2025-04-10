#include "raylib.h"
#include "config.h"

void DrawWave(float *buffer, int frames, int width, int height) {
    ClearBackground(BLACK);
    for (int i = 0; i < frames - 1; i++) {
        int x1 = (i * width) / frames;
        int x2 = ((i + 1) * width) / frames;
        float sample1 = buffer[i] * AMPLIFY;
        float sample2 = buffer[i + 1] * AMPLIFY;
        DrawLine(x1, height / 2 - sample1, x2, height / 2 - sample2, GREEN);
    }
}
