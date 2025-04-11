/*
 * File: audio_input.c
 * Description: Implementation of live audio input capture.
 * C89 compliant.
 */

 #include "audio_input.h"
 #include <string.h>
 
 float inputBuffer[MAX_INPUT_SAMPLES];
 int inputBufferSize = 0;
 
 /* Internal callback for live input */
 static void input_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
 {
     if (pInput != NULL && frameCount <= MAX_INPUT_SAMPLES) {
         memcpy(inputBuffer, pInput, frameCount * sizeof(float));
         inputBufferSize = (int)frameCount;
     }
     (void)pOutput;
 }
 
 /* Initialize a capture device */
 int InitLiveInput(ma_device *device)
 {
     ma_device_config config;
     config = ma_device_config_init(ma_device_type_capture);
     config.capture.format = ma_format_f32;
     config.capture.channels = 1;
     config.sampleRate = 44100;
     config.dataCallback = input_callback;
     config.pUserData = NULL;
 
     if (ma_device_init(NULL, &config, device) != MA_SUCCESS) {
         return -1;
     }
 
     return ma_device_start(device);
 }
 
 void CleanupLiveInput(ma_device *device)
 {
     ma_device_uninit(device);
 }
 