/* 
 * File: audio.c
 * Description: Audio module implementation for initializing, processing,
 * and cleaning up audio playback and capture.
 * C89 compliant.
 */

 #include "audio.h"
 #include <string.h>
 #include <stddef.h> /* for NULL */
 #include "config.h"
 
 /* Global pointer to hold reference to audio state. */
 static AudioState *g_audio_state;
 
 /*
  * Function: data_callback
  * Description: Playback callback; fills the output buffer by reading from the decoder.
  * Parameters:
  *   pDevice    - pointer to the ma_device structure.
  *   pOutput    - pointer to output buffer.
  *   pInput     - pointer to input buffer (unused).
  *   frameCount - number of frames requested.
  */
 static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
 {
     ma_decoder* decoder;
     decoder = (ma_decoder*)pDevice->pUserData;
     if (decoder == NULL) {
         return;
     }
     ma_decoder_read_pcm_frames(decoder, pOutput, frameCount, NULL);
     if (frameCount <= MAX_BUFFER_SIZE) {
         memcpy(g_audio_state->buffer, pOutput, frameCount * sizeof(float));
         g_audio_state->bufferSize = (int)frameCount;
     }
     (void)pInput;
 }
 
 /*
  * Function: InitAudio
  * Description: Initialize audio playback by decoding a file.
  */
 int InitAudio(const char *filename, ma_decoder *decoder, ma_device *device, AudioState *state)
 {
     ma_result result;
     ma_decoder_config config;
     ma_device_config devConfig;
 
     g_audio_state = state;
 
     config = ma_decoder_config_init(ma_format_f32, 1, 44100);
     result = ma_decoder_init_file(filename, &config, decoder);
     if (result != MA_SUCCESS) {
         return -1;
     }
 
     devConfig = ma_device_config_init(ma_device_type_playback);
     devConfig.playback.format   = decoder->outputFormat;
     devConfig.playback.channels = decoder->outputChannels;
     devConfig.sampleRate        = decoder->outputSampleRate;
     devConfig.dataCallback      = data_callback;
     devConfig.pUserData         = decoder;
 
     result = ma_device_init(NULL, &devConfig, device);
     if (result != MA_SUCCESS) {
         return -1;
     }
 
     return ma_device_start(device);
 }
 
 /*
  * Function: capture_callback
  * Description: Capture callback; writes captured audio into the state buffer.
  */
 static void capture_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
 {
     if (frameCount <= MAX_BUFFER_SIZE) {
         memcpy(g_audio_state->buffer, pInput, frameCount * sizeof(float));
         g_audio_state->bufferSize = (int)frameCount;
     }
     (void)pOutput;
 }
 
 /*
  * Function: InitAudioCapture
  * Description: Initialize audio capture from a virtual audio device.
  */
 int InitAudioCapture(ma_device *device, AudioState *state)
 {
     ma_result result;
     ma_device_config devConfig;
 
     g_audio_state = state;
 
     devConfig = ma_device_config_init(ma_device_type_capture);
     /* Configure capture-specific parameters: */
     devConfig.capture.format   = ma_format_f32;
     devConfig.capture.channels = 1;
     devConfig.sampleRate       = 44100;
     devConfig.dataCallback     = capture_callback;
     devConfig.pUserData        = NULL;
 
     result = ma_device_init(NULL, &devConfig, device);
     if (result != MA_SUCCESS) {
         return -1;
     }
 
     return ma_device_start(device);
 }
 
 /*
  * Function: CleanupAudio
  * Description: Clean up audio device and decoder.
  */
 void CleanupAudio(ma_device *device, ma_decoder *decoder)
{
    if (device != NULL) {
        ma_device_uninit(device);
    }
    if (decoder != NULL) {
        ma_decoder_uninit(decoder);
    }
}

 