#include "filters.h"

void ApplyGain(float *buffer, int count, float gain) {
    int i;
    for (i = 0; i < count; i++) {
        buffer[i] *= gain;
    }
}
