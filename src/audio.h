/* 
 * File: audio.h
 * Description: Audio module interface for initializing, processing, 
 * and cleaning up audio playback.
 * C89 compliant.
 */

 #ifndef AUDIO_H
 #define AUDIO_H
 
 #include "miniaudio.h"
 #include "config.h"
 
 /* Structure to hold audio state */
 typedef struct {
     float buffer[MAX_BUFFER_SIZE];
     int bufferSize;
 } AudioState;
 
 /* 
  * Function: InitAudio
  * Description: Initialize audio decoding and playback.
  * Parameters:
  *   filename - path to the audio file
  *   decoder  - pointer to a ma_decoder structure (will be initialized)
  *   device   - pointer to a ma_device structure (will be initialized)
  *   state    - pointer to AudioState that holds the playback buffer.
  * Returns:
  *   0 on success, non-zero on failure.
  */
 int InitAudio(const char *filename, ma_decoder *decoder, ma_device *device, AudioState *state);
 
 /* 
  * Function: CleanupAudio
  * Description: Clean up and free resources associated with the audio device and decoder.
  * Parameters:
  *   device  - pointer to the ma_device to be uninitialized.
  *   decoder - pointer to the ma_decoder to be uninitialized.
  */
 void CleanupAudio(ma_device *device, ma_decoder *decoder);
 
 #endif /* AUDIO_H */

 