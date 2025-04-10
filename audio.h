#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"
#include "config.h"  

typedef struct {
    float buffer[MAX_BUFFER_SIZE];
    int bufferSize;
} AudioState;

int InitAudio(const char *filename, ma_decoder *decoder, ma_device *device, AudioState *state);
void CleanupAudio(ma_device *device, ma_decoder *decoder);

#endif
