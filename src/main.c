/* 
 * File: main.c
 * Description: Main entry point for the WaveLab application.
 * Initializes audio (playback or capture), processes user input, applies filters, and draws waveform.
 * C89 compliant.
 */

 #include "raylib.h"
 #include "config.h"
 #include "audio.h"
 #include "wave.h"
 #include "filters.h"
 #include "ui.h"
 #include "miniaudio.h"
 #include <string.h>
 #include "audio_input.h"
 
 #define MINIAUDIO_IMPLEMENTATION
 #define SAMPLE_FILE "sample.wav"
 
 int main(int argc, char *argv[])
{
    int testMode = 0;
    int liveMode = 0;
    int i;
    ma_decoder decoder;
    ma_device device;
    AudioState state;
    float gain;

    /* Parse command-line args */
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--test") == 0) {
            testMode = 1;
        } else if (strcmp(argv[i], "--live") == 0) {
            liveMode = 1;
        }
    }

    InitWindow(WIDTH, HEIGHT, testMode ? "WaveLab (Test Mode)" :
                                      (liveMode ? "WaveLab (Live Input)" : "WaveLab"));
    SetTargetFPS(testMode ? 10 : 60);

    gain = 1.0f;
    state.bufferSize = 0;

    if (testMode) {
        if (InitAudio(SAMPLE_FILE, &decoder, &device, &state) != 0) {
            CloseWindow();
            return 1;
        }
    } else if (liveMode) {
        if (InitLiveInput(&device) != 0) {
            CloseWindow();
            return 1;
        }
    }

    while (!WindowShouldClose()) {
        HandleInput(&gain);

        if (testMode) {
            ApplyGain(state.buffer, state.bufferSize, gain);
        } else if (liveMode) {
            ApplyGain(inputBuffer, inputBufferSize, gain);
        }

        BeginDrawing();
        if (testMode) {
            DrawWave(state.buffer, state.bufferSize, WIDTH, HEIGHT);
        } else if (liveMode) {
            DrawWave(inputBuffer, inputBufferSize, WIDTH, HEIGHT);
        }
        EndDrawing();
    }

    if (testMode) {
        CleanupAudio(&device, &decoder);
    } else if (liveMode) {
        CleanupLiveInput(&device);
    }

    CloseWindow();
    return 0;
}
 