/* 
 * File: filters.h
 * Description: Audio filtering functions.
 * C89 compliant.
 */

 #ifndef FILTERS_H
 #define FILTERS_H
 
 /* 
  * Function: ApplyGain
  * Description: Applies gain to a buffer of audio samples.
  * Parameters:
  *   buffer - pointer to the audio samples array
  *   count  - number of audio samples in the buffer
  *   gain   - gain multiplier to apply
  */
 void ApplyGain(float *buffer, int count, float gain);
 
 #endif /* FILTERS_H */

 