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

typedef struct BOOT_ANIMATION {
    bool status;
    uint16_t timer;
    struct BOOT_ORIGIN {
        uint8_t x;
        uint8_t y;
    } origin;
} BOOT_ANIMATION;

#ifdef LAYER_STATE_8BIT
    extern struct RGB_INDICATOR indicator_matrix[8];
    extern struct RGB_INDICATOR indicator_underglow[8];
#else
#   error Only supports up to 8 layers for now.
#endif

#define STARTUP_ANIM_TIME 2500

// Boot animation start position
#ifndef BOOT_ANIM_X
  #define BOOT_ANIM_X 30
#endif
#ifndef BOOT_ANIM_Y
  #define BOOT_ANIM_Y 0
#endif

//HSV SPLASH_math_boot(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);
void rgb_matrix_boot_anim_starter(BOOT_ANIMATION *boot, uint8_t originx, uint8_t originy);
void rgb_matrix_boot_anim_runner(BOOT_ANIMATION *boot, uint8_t led_min, uint8_t led_max);
void rgb_matrix_boot_anim_end (BOOT_ANIMATION *boot);

// add sub-layer below user level to avoid conflicts at user/keyboard level
bool process_record_rgb(uint16_t keycode, keyrecord_t *record);
bool rgb_matrix_indicators_advanced_rgb(uint8_t led_min, uint8_t led_max);
void keyboard_post_init_rgb(void);
void suspend_power_down_rgb(void);
void suspend_wakeup_init_rgb(void);
