/* 
 * File: filters.c
 * Description: Implementation of audio filtering functions.
 * C89 compliant.
 */

 #include "filters.h"

 /* 
  * Function: ApplyGain
  * Description: Applies gain to a buffer of audio samples.
  */
 void ApplyGain(float *buffer, int count, float gain)
 {
     int i;
     for (i = 0; i < count; i++) {
         buffer[i] *= gain;
     }
 }
