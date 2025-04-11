/* 
 * File: wave.h
 * Description: Waveform drawing functions.
 * C89 compliant.
 */

 #ifndef WAVE_H
 #define WAVE_H
 
 /* 
  * Function: DrawWave
  * Description: Draws waveform representation of audio data.
  * Parameters:
  *   buffer - pointer to the audio sample buffer
  *   frames - number of frames in the audio buffer
  *   width  - width of the drawing canvas
  *   height - height of the drawing canvas
  */
 void DrawWave(float *buffer, int frames, int width, int height);
 
 #endif /* WAVE_H */

 