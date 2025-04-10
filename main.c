#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "raylib.h"

#include "config.h"
#include "audio.h"
#include "wave.h"
#include "filters.h"
#include "ui.h"

#define SAMPLE_FILE "sample.wav"

int main(void) {
    InitWindow(WIDTH, HEIGHT, "WaveLab");
    SetTargetFPS(60);

    ma_decoder decoder;
    ma_device device;
    AudioState state = {0};
    float gain = 1.0f;

    if (InitAudio(SAMPLE_FILE, &decoder, &device, &state) != 0) {
        CloseWindow();
        return 1;
    }

    while (!WindowShouldClose()) {
        HandleInput(&gain);
        ApplyGain(state.buffer, state.bufferSize, gain);

        BeginDrawing();
        DrawWave(state.buffer, state.bufferSize, WIDTH, HEIGHT);
        EndDrawing();
    }

    CleanupAudio(&device, &decoder);
    CloseWindow();
    return 0;
}
