/*
 * File: audio_input.h
 * Description: Interface for handling live audio input.
 * C89 compliant.
 */

 #ifndef AUDIO_INPUT_H
 #define AUDIO_INPUT_H
 
 #include "miniaudio.h"
 #include "config.h"
 
 #define MAX_INPUT_SAMPLES 4096
 
 extern float inputBuffer[MAX_INPUT_SAMPLES];
 extern int inputBufferSize;
 
 int InitLiveInput(ma_device *device);
 void CleanupLiveInput(ma_device *device);
 
 #endif /* AUDIO_INPUT_H */
 