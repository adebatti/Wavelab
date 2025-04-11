/* 
 * File: ui.c
 * Description: Implementation of user interface input handling.
 * C89 compliant.
 */

 #include "raylib.h"
 #include "ui.h"
 
 /* 
  * Function: HandleInput
  * Description: Adjusts the gain value based on user key input.
  */
 void HandleInput(float *gain)
 {
     if (IsKeyPressed(KEY_UP)) {
         *gain = *gain * 1.1f;
     } else if (IsKeyPressed(KEY_DOWN)) {
         *gain = *gain * 0.9f;
     }
 }
