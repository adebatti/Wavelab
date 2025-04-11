/* 
 * File: wave.c
 * Description: Implementation of waveform drawing functions.
 * C89 compliant.
 */

 #include "raylib.h"
 #include "config.h"
 #include "wave.h"
 
 /* 
  * Function: DrawWave
  * Description: Draws the waveform of the audio data.
  */
 void DrawWave(float *buffer, int frames, int width, int height)
 {
     int i;
     /* Clear the background */
     ClearBackground(BLACK);
     for (i = 0; i < frames - 1; i++) {
         int x1, x2;
         float sample1, sample2;
         
         x1 = (i * width) / frames;
         x2 = ((i + 1) * width) / frames;
         sample1 = buffer[i] * AMPLIFY;
         sample2 = buffer[i + 1] * AMPLIFY;
         DrawLine(x1, height / 2 - (int)sample1, x2, height / 2 - (int)sample2, GREEN);
     }
 }
