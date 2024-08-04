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

#include QMK_KEYBOARD_H
#include "custom_rgb.h"
#include "bryan065.h"
#include <lib/lib8tion/lib8tion.h>

/* Structure for 'struct RGB_INDICATOR' layer indicator effect
 *   Note: Layer 0 aka base layer should never show any RGB layer indication
 *
 *   {flag, hsv, flag_op1, hsv_op1}
 *
 *   FLAG:
 *     TRUE  = Primary custom indicator
 *     FALSE = Transparent, will show user RGB mode/animation
 *   FLAG_OP1:
 *     TRUE  = Secondary custom indicator
 *     FALSE = Transparent
 *
 *   HUE:
 *     Color of the primary layer indicator effect
 *   HUE_OP1:
 *     Color of the secondary layer indicator effect
 *
 *   SATURATION:
 *     Saturation of the primary layer indicator effect
 *   SATURATION_OP1:
 *     Saturation of the secondary layer indicator effect
 *
 *   VALUE:
 *     Brightness of the primary layer indicator effect
 *          No layer indicator   = 0
 *          Follow user settings = 1
 *          Fixed brightness     = 2-255
 *          Full brightness      = RGB_MATRIX_MAXIMUM_BRIGHTNESS
 *
 *   VALUE_OP1:
 *     Brightness of the secondary layer indicator effect
 *          No layer indicator   = 0
 *          Follow user settings = 1
 *          Fixed brightness     = 2-255
 *          Full brightness      = RGB_MATRIX_MAXIMUM_BRIGHTNESS
 *
 */
__attribute__((weak))
struct RGB_INDICATOR indicator_matrix[8] = {
    // Layer 0, base layer, should have no effect
    {   NULL,           // true/false: show layer indicator on matrix
        {0, 0, 0},      // Matrix  layer indicator HSV
        NULL,           // true/false: show per-key indicator
        {0, 0, 0}       // Per-key layer indicator HSV
    },
    {   false,           // Layer 1
        {0, 255, 0},
        false,
        {0, 0, 0}
    },
    {   false,           // Layer 2
        {0, 255, 0},
        false,
        {0, 0, 0}
    },
    {   false,           // Layer 3
        {0, 255, 0},
        false,
        {0, 0, 0}
    },
    {   false,           // Layer 4
        {0, 255, 0},
        false,
        {0, 0, 0}
    },
    {   false,           // Layer 5
        {0, 255, 0},
        false,
        {0, 0, 0}
    },
    {   false,           // Layer 6
        {0, 255, 0},
        false,
        {0, 0, 0}
    },
    {   false,           // Layer 7
        {0, 255, 0},
        false,
        {0, 0, 0}
    },
};

__attribute__((weak))
struct RGB_INDICATOR indicator_underglow[8] = {
    // Layer 0, base layer, should have no effect
    {   NULL,           // true/false: show layer indicator on underglow
        {0, 0, 0}      // Underglow layer indicator HSV
    },
    {   false,           // Layer 1
        {0, 255, 0}
    },
    {   false,           // Layer 2
        {0, 255, 0}
    },
    {   false,           // Layer 3
        {0, 255, 0}
    },
    {   false,           // Layer 4
        {0, 255, 0}
    },
    {   false,           // Layer 5
        {0, 255, 0}
    },
    {   false,           // Layer 6
        {0, 255, 0}
    },
    {   false,           // Layer 7
        {0, 255, 0}
    }
};

__attribute__((weak)) bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return rgb_matrix_indicators_advanced_rgb(led_min, led_max);
}

__attribute__((weak)) bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_rgb(keycode, record);
}

__attribute__((weak)) void keyboard_post_init_user(void) {
    keyboard_post_init_rgb();
}

__attribute__((weak)) void suspend_power_down_user(void) {
    suspend_power_down_rgb();
}

__attribute__((weak)) void suspend_wakeup_init_user(void) {
    suspend_wakeup_init_rgb();
}



HSV          rgb_original_hsv;
uint16_t     boot_timer;
int8_t       boot_status = 0;
bool         rgb_mod_flag;

//===============Custom Functions=========================//

// Splash animation math
HSV SPLASH_math2(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    hsv.h += effect;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
} // End of splash math functions

// Boot animation, run only if RGB_MATRIX_ENABLED is defined and if the matrix is enabled.
void rgb_matrix_boot_anim(uint8_t boot_anim) {
    #if defined(RGB_MATRIX_ENABLE)
        if (rgb_matrix_config.enable) {
            rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, RGB_MATRIX_MAXIMUM_BRIGHTNESS);   // Set brightness to maximum allowed before playing animation
            rgb_matrix_set_speed_noeeprom(64);                                                                              // Set animation speed to default before playing animation
            boot_timer = timer_read();
            boot_status = boot_anim;
        }
    #endif
} // End of boot animation

//===============Custom Functions End=====================//

//==============Layer indicator code==============//
layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            if (rgb_mod_flag != false) { rgb_mod_flag = false; }    // Set rgb_mod_flag to false on the default layer
            break;                                                  // This is to disable per-key indicator on the default layer
    }
    return state = layer_state_set_user(state);
}

/* Boot_status
*   1 = Run splash boot animation
*   0 = Don't run anim / anim complete
*/

bool rgb_matrix_indicators_advanced_rgb(uint8_t led_min, uint8_t led_max) {
    // Boot animation
    void rgb_matrix_boot_anim_runner(uint8_t originx, uint8_t originy) {
        for (uint8_t i = led_min; i < led_max; i++) {
                    HSV hsv = rgb_matrix_config.hsv;
                    hsv.v   = 0;
                    for (uint8_t j = 0; j < 1; j++) {
                        int16_t  dx   = g_led_config.point[i].x - originx;     // X origin of splash animation
                        int16_t  dy   = g_led_config.point[i].y - originy;     // y origin of splash animation
                        uint8_t  dist = sqrt16(dx * dx + dy * dy);
                        uint16_t tick = scale16by8(timer_elapsed(boot_timer), qadd8(rgb_matrix_config.speed, 1));
                        hsv           = SPLASH_math2(hsv, dx, dy, dist, tick);
                    }
                    hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
    }

     // Boot animation Code
    switch(boot_status) {
    case 1:
        if (timer_elapsed(boot_timer) >= STARTUP_ANIM_TIME) {                                                   // If timer is > boot animation time, load the saved RGB mode and fade in
            rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_original_hsv.v);  // Reset HSV.v to original value
            rgb_matrix_set_speed_noeeprom(rgb_matrix_config.speed);                                             // Reset speed to original value
            eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
            rgb_matrix_mode_noeeprom(rgb_matrix_config.mode);                                                   // Load original mode
            boot_status = 0;
        } else {                                                                                                // Otherwise, run boot animation
            rgb_matrix_boot_anim_runner(BOOT_ANIM_X,BOOT_ANIM_Y);
        }
        break;
    case 2:
        if (timer_elapsed(boot_timer) >= STARTUP_ANIM_TIME) {                                                   // If timer is > boot animation time, load the saved RGB mode and fade in
            rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_original_hsv.v);  // Reset HSV.v to original value
            rgb_matrix_set_speed_noeeprom(rgb_matrix_config.speed);                                             // Reset speed to original value
            rgb_matrix_disable_noeeprom();

            boot_status = 0;
        } else {                                                                                                // Otherwise, run boot animation
            rgb_matrix_boot_anim_runner(112,64);
        }
        break;
    }   // End boot animation code

    // Layer indicator code
    if (get_highest_layer(layer_state) > 0 && !rgb_mod_flag) {
        uint8_t layer = get_highest_layer(layer_state);

        // Underglow layer indication
        HSV underglow_hsv = indicator_underglow[layer].hsv;
        if (indicator_underglow[layer].hsv.v == 1) {
            underglow_hsv.v = rgb_matrix_config.hsv.v;
        }
        else if (indicator_underglow[layer].hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
            underglow_hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
        }

        //apply the colors to the layers, if configured. Otherwise, the user's RGB mode will show through
        if (indicator_underglow[layer].flag) {
            for (uint8_t i = led_min; i <= led_max; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], 0x02)) { // 0x02 == LED_FLAG_UNDERGLOW
                    RGB underglow_rgb = hsv_to_rgb(underglow_hsv);
                    rgb_matrix_set_color(i, underglow_rgb.r, underglow_rgb.g, underglow_rgb.b);
                }
            }
        } // End of underglow layer indicator

        // Layer indicator ONLY on the RGB_MATRIX (not underglow, excluding per key indicator)
        HSV matrix_hsv = indicator_matrix[layer].hsv;
        if (indicator_matrix[layer].hsv.v == 1) {
            matrix_hsv.v = rgb_matrix_config.hsv.v;
        }
        else if (indicator_matrix[layer].hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
            matrix_hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
        }

        // Per Key indicator ONLY on the RGB_MATRIX
        HSV perkey_hsv = indicator_matrix[layer].hsv_op;
        if (indicator_matrix[layer].hsv_op.v == 1) {
            perkey_hsv.v = rgb_matrix_config.hsv.v;
        }
        else if (indicator_matrix[layer].hsv_op.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
            perkey_hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
        }

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                // Comparing LED index to matrix for configured keys or override keys
                if (index >= led_min && index <= led_max && index != NO_LED) {

                    uint16_t keycheck = keymap_key_to_keycode(layer, (keypos_t){col,row});

                    // If key is configured aka _NOT_ KC_TRNS, set keys to a specific color:
                    // Per key overrides
                    switch (keycheck) {
                        case QK_BOOT:
                            perkey_hsv.h = 0;  // RED
                            perkey_hsv.s = 255;
                            break;
                        case LCTL(KC_BSPC):
                            perkey_hsv.h = 0;  // RED
                            perkey_hsv.s = 255;
                            break;
                        case EE_CLR:
                            perkey_hsv.h = 0;  // RED
                            perkey_hsv.s = 255;
                            break;

                        /* Per key overrides with toggle colors
                            *
                            *   Set the hue in the first `if statement`  for the color when toggled on
                            *   Set the hue in the second `if statement` for the color when toggled off
                            *      If you don't want to set a second color when toggled off, replace `hsv.h` with `goto perkey;`
                            *
                            *  hsv.h = hue
                            *  hsv.s = saturation
                            *  hsv.v = DO NOT CHANGE
                            */
                        case NK_TOGG:
                            if (keymap_config.nkro == 1) {
                                perkey_hsv.h = 85; // GREEN if nkro is enabled
                                perkey_hsv.s = 255;
                            } else {
                                //perkey_hsv.h = 0 ; // RED if nkro is enabled. Comment out to keep same color as the rest of the perkey
                                //perkey_hsv.s = 255;
                                goto perkey;
                            }
                            break;
                        case GU_TOGG:
                            if (keymap_config.no_gui == 1) {
                                perkey_hsv.h = 0;  // RED if GUI is disabled
                                perkey_hsv.s = 255;
                            } else {
                                //per_key.hsv.h = 85; // GREEN if GUI is enabled. Comment out to keep same color as the rest of the perkey
                                //perkey_hsv.s = 255;
                                goto perkey;
                            }
                            break;
                        default:
                        perkey:
                            perkey_hsv.h = indicator_matrix[layer].hsv_op.h;
                            perkey_hsv.s = indicator_matrix[layer].hsv_op.s;
                            break;
                    }

                    if (keycheck > KC_TRNS) {
                        // Apply color to configured keys aka per-key indicator
                        if (indicator_matrix[layer].flag_op) {
                            RGB perkey_rgb = hsv_to_rgb(perkey_hsv);
                            rgb_matrix_set_color(index, perkey_rgb.r, perkey_rgb.g, perkey_rgb.b);
                        }
                    } else {
                        //Apply colors to the non-configured keys aka layer indicator. Otherwise, the user's RGB mode will show through
                        if (indicator_matrix[layer].flag) {
                            RGB matrix_rgb = hsv_to_rgb(matrix_hsv);
                            rgb_matrix_set_color(index, matrix_rgb.r, matrix_rgb.g, matrix_rgb.b);
                        }
                    }
                } // End of comparison code
            }
        } // End of per configured key indicator

    } // End of layer indicator code

    #if defined(PRODUCT) && USB_DEVICE_PRODUCT_NAME == Cyber77
        // Caps lock / num lock code
        if (host_keyboard_led_state().caps_lock) {
            HSV hsv = rgb_matrix_config.hsv;
            hsv.s = 1;                                                                  // Use white LED for indicator

            if (hsv.v < 100) { hsv.v = 100; }                                           // Ensure the caps/num lock has a minimum brightness and doesn't exceed the defined max brightness
            else if (hsv.v < (RGB_MATRIX_MAXIMUM_BRIGHTNESS - 30)) { hsv.v += 30; }     //   Also makes the caps/num lock a bit brighter than the rest of the LED's
            else { hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS; }


            RGB rgb = hsv_to_rgb(hsv);
            RGB_MATRIX_INDICATOR_SET_COLOR(3, rgb.r, rgb.g, rgb.b);                     // Assuming caps lock is at led #3
        }
        if (host_keyboard_led_state().num_lock) {
            HSV hsv = rgb_matrix_config.hsv;
            hsv.s = 1;

            if (hsv.v < 100) { hsv.v = 100; }
            else if (hsv.v < (RGB_MATRIX_MAXIMUM_BRIGHTNESS - 30)) { hsv.v += 30; }
            else { hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS; }

            RGB rgb = hsv_to_rgb(hsv);
            RGB_MATRIX_INDICATOR_SET_COLOR(5, rgb.r, rgb.g, rgb.b);                     // Assuming num lock is at led #5
        } // End of caps/num lock code
    #endif
    return true;
}
//==============Layer indicator code end==========//

//==========RGB init/suspend functions========//
void keyboard_post_init_rgb(void) {
    // Fade in RGB when first plugging in kb or on resume from sleep
    #if (defined (RGB_MATRIX_ENABLE))
        rgb_matrix_boot_anim(1);
    #endif
}

void suspend_power_down_rgb(void) {
    // code will run multiple times while keyboard is suspended
}

void suspend_wakeup_init_rgb(void) {
    // Fade in RGB when first plugging in kb or on resume from sleep
    #if (defined (RGB_MATRIX_ENABLE))
        rgb_matrix_boot_anim(1);
    #endif
}
//=======RGB init/suspend functions End=======//

//=================Keycode Functions ================//
bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_MODE_FORWARD ... RGB_SPD:      // Add rgb_mod_flag = true to all RGB modification keys.
            if (!record->event.pressed) {
                rgb_mod_flag = true;            //   This is to let the per key indicator know to stop if the RGB settings are modified so
                                                //   the user can see the changes again without the layer indicator in the way
            }
            return true;
        case MON_OFF:
            if (!record->event.pressed) {
                #if defined(RGB_MATRIX_ENABLE)
                    rgb_matrix_boot_anim(2);
                #endif
            }
            return true;
        case RGB_TOG:   // Override original RGB_TOG function to handle RGB_MATRIX caps/numlock indicator
            #if defined(RGB_MATRIX_ENABLE) && (defined(PRODUCT) && USB_DEVICE_PRODUCT_NAME == Cyber77)
            if (!record->event.pressed) {
                    if (rgb_matrix_config.hsv.v > 0) {
                        rgb_original_hsv = rgb_matrix_config.hsv;
                        rgb_matrix_sethsv_noeeprom( rgb_original_hsv.h, rgb_original_hsv.s, 0);
                    } else {
                        rgb_matrix_sethsv_noeeprom( rgb_original_hsv.h, rgb_original_hsv.s, rgb_original_hsv.v);
                    }
            }
            #endif
            return false;
        case RGB_DEF:
            #ifdef RGB_MATRIX_ENABLE
            if (record->event.pressed) {
                // Set default mode
                #ifdef RGB_MATRIX_DEFAULT_MODE
                    rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
                #else
                    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                #endif

                // Set default speed/hue/saturation
                rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
                rgb_matrix_sethsv(RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL);
            } else {
                rgb_mod_flag = true;
            }
            #endif
            return false;
        default:
            return true;
    }
}
//==============Keycode Functions End=============//
