#include "audio.h"
#include <string.h>
#include "config.h"

static AudioState *audioStateRef;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_decoder* decoder = (ma_decoder*)pDevice->pUserData;
    if (decoder == NULL) return;

    ma_decoder_read_pcm_frames(decoder, pOutput, frameCount, NULL);

    if (frameCount <= MAX_BUFFER_SIZE) {
        memcpy(audioStateRef->buffer, pOutput, frameCount * sizeof(float));
        audioStateRef->bufferSize = frameCount;
    }

    (void)pInput;
}

int InitAudio(const char *filename, ma_decoder *decoder, ma_device *device, AudioState *state) {
    ma_result result;
    audioStateRef = state;

    ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 1, 44100);
    result = ma_decoder_init_file(filename, &config, decoder);
    if (result != MA_SUCCESS) return -1;

    ma_device_config devConfig = ma_device_config_init(ma_device_type_playback);
    devConfig.playback.format   = decoder->outputFormat;
    devConfig.playback.channels = decoder->outputChannels;
    devConfig.sampleRate        = decoder->outputSampleRate;
    devConfig.dataCallback      = data_callback;
    devConfig.pUserData         = decoder;

    result = ma_device_init(NULL, &devConfig, device);
    if (result != MA_SUCCESS) return -1;

    return ma_device_start(device);
}

void CleanupAudio(ma_device *device, ma_decoder *decoder) {
    ma_device_uninit(device);
    ma_decoder_uninit(decoder);
}
