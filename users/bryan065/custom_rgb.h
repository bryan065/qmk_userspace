/*
  Copyright (c) 2022 Bryan065

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#pragma once

#if !defined( CUSTOM_RGB_H )
#define CUSTOM_RGB_H
#endif

// Per layer RGB options
struct RGB_INDICATOR {
    bool flag;
    HSV hsv;
    bool flag_op;
    HSV hsv_op;
};

extern struct RGB_INDICATOR indicator_matrix[8];
extern struct RGB_INDICATOR indicator_underglow[8];

// Define custom values if not defined in config.h
#if STARTUP_ANIM_TIME < 0
#   error STARTUP_ANIM_TIME must be greater than 0
#elif !defined (STARTUP_ANIM_TIME)
#   define STARTUP_ANIM_TIME 2200
#endif

// Boot animation start position
#ifndef BOOT_ANIM_X
  #define BOOT_ANIM_X 30
#endif
#ifndef BOOT_ANIM_Y
  #define BOOT_ANIM_Y 0
#endif

HSV SPLASH_math2(HSV, int16_t, int16_t, uint8_t, uint16_t);
void rgb_matrix_boot_anim(uint8_t );

// add sub-layer below user level to avoid conflicts at user/keyboard level
bool process_record_rgb(uint16_t keycode, keyrecord_t *record);
bool rgb_matrix_indicators_advanced_rgb(uint8_t led_min, uint8_t led_max);
void keyboard_post_init_rgb(void);
void suspend_power_down_rgb(void);
void suspend_wakeup_init_rgb(void);
