/* 
 * File: main.c
 * Description: Main entry point for the WaveLab application.
 * Initializes audio, processes user input, applies filters, and draws waveform.
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

 #define MINIAUDIO_IMPLEMENTATION
 #define SAMPLE_FILE "sample.wav"
 
 int main(int argc, char *argv[])
 {
    int testMode = 0;
    ma_decoder decoder;
    ma_device device;
    AudioState state;
    float gain;

    /* Check for command-line flag */
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        testMode = 1;
    }

    /* Init window */
    InitWindow(WIDTH, HEIGHT, testMode ? "WaveLab (Test Mode)" : "WaveLab");
    SetTargetFPS(testMode ? 10 : 60);  /* Lower FPS for testing */

     /* Initialize state */
     gain = 1.0f;
     state.bufferSize = 0;
     
     /* Initialize the Raylib window */
     InitWindow(WIDTH, HEIGHT, "WaveLab");
     SetTargetFPS(60);
     
     if (InitAudio(SAMPLE_FILE, &decoder, &device, &state) != 0) {
         CloseWindow();
         return 1;
     }
     
     while (!WindowShouldClose()) {
         /* Handle user input */
         HandleInput(&gain);
         
         /* Apply gain filter */
         ApplyGain(state.buffer, state.bufferSize, gain);
         
         BeginDrawing();
         /* Draw the waveform */
         DrawWave(state.buffer, state.bufferSize, WIDTH, HEIGHT);
         EndDrawing();
     }
     
     CleanupAudio(&device, &decoder);
     CloseWindow();
     return 0;
 }

