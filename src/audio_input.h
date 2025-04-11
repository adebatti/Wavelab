/*
 * File: audio_input.h
 * Description: Interface for handling live audio input.
 * C89 compliant.
 */

 #ifndef AUDIO_INPUT_H
 #define AUDIO_INPUT_H
 
 #include <stddef.h>  /* for NULL */
 #include "miniaudio.h"
 
 #define MAX_INPUT_SAMPLES 4096
 
 extern float inputBuffer[MAX_INPUT_SAMPLES];
 extern int inputBufferSize;
 
 void StartLiveInput(void);
 void StopLiveInput(void);
 void ReadLiveSamples(float *buffer, int count);
 
 #endif /* AUDIO_INPUT_H */
