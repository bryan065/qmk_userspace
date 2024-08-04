/*
  Copyright (c) 2022 Bryan065

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "bryan065.h"
#include "version.h"

// Comment out to disable custom RGB features
#include "custom_rgb.h"

/* Structure for 'struct RGB_INDICATOR' layer indicator effect
 *   Note: Layer 0 aka base layer should never show any RGB layer indication
 *
 *   {  flag,
        hsv {hue, sat, value},
        flag_op1,
        hsv_op {hue_op, sat_op, val_op}
     }
 *
 *   FLAG:
 *     TRUE  = Primary custom indicator
 *     FALSE = Transparent, will show user RGB mode/animation
 *   FLAG_OP:
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
 *   SATURATION_OP:
 *     Saturation of the secondary layer indicator effect
 *
 *   VALUE:
 *     Brightness of the primary layer indicator effect
 *          No layer indicator   = 0 (LEDs off)
 *          Follow user settings = 1
 *          Fixed brightness     = 2-255
 *          Full brightness      = RGB_MATRIX_MAXIMUM_BRIGHTNESS
 *
 *   VALUE_OP:
 *     Brightness of the secondary layer indicator effect
 *          No layer indicator   = 0 (LEDs off)
 *          Follow user settings = 1
 *          Fixed brightness     = 2-255
 *          Full brightness      = RGB_MATRIX_MAXIMUM_BRIGHTNESS
 *
 */

#ifdef CUSTOM_RGB_H

struct RGB_INDICATOR indicator_matrix[8] = {
    {   NULL            // _BASE - no effect
    },
    {   false,          // _FUNCTION indicator
        {0, 0, 0},
        true,           // _FUNCTION per-key
        {0, 1, 1}
    },
    {   true,           // _RGB indicator
        {0, 255, 0},
        true,           // _RGB per-key
        {0, 1, 1}
    },
    {   true,           // _SYSTEM indicator
        {0, 255, 0},
        true,           // _SYSTEM per-key
        {0, 1, 1}
    }
};

struct RGB_INDICATOR indicator_underglow[8] = {
    {   NULL            // _BASE - no effect
    },
    {   false,          // _FUNCTION underglow
        {0, 255, 0}
    },
    {   true,           // _RGB underglow
        {120, 255, 1}
    },
    {   true,           // _SYSTEM underglow
        {0, 255, 1}
    }
};

#endif

//============Tap Dance Functions===================//
#ifdef TAP_DANCE_ENABLE
    typedef enum {
        TD_NONE,
        TD_UNKNOWN,
        TD_SINGLE_TAP,
        TD_SINGLE_HOLD,
        TD_DOUBLE_TAP,
        TD_DOUBLE_HOLD
    } td_state_t;

    typedef struct {
        bool is_press_action;
        uint8_t state;
    } td_tap_t;

    // Tap dance keycodes
    enum {
        TD_SYS_QL
    };

    // Function associated with all tap dances
   td_state_t cur_dance(tap_dance_state_t *state);

    // Functions associated with individual tap dances
    void ql_finished(tap_dance_state_t *state, void *user_data);
    void ql_reset(tap_dance_state_t *state, void *user_data);

    // Determine the current tap dance state
    td_state_t cur_dance(tap_dance_state_t *state) {
        if (state->count == 1) {
            if (!state->pressed) return TD_SINGLE_TAP;
            else return TD_SINGLE_HOLD;
        } else if (state->count == 2) {
            if (!state->pressed) return TD_DOUBLE_TAP;
            else return TD_DOUBLE_HOLD;
        }
        else return TD_UNKNOWN;
    }

    // Initialize tap structure associated with example tap dance key
    static td_tap_t ql_tap_state = {
        .is_press_action = true,
        .state = TD_NONE
    };

    // Functions that control what our tap dance key does
    void ql_finished(tap_dance_state_t *state, void *user_data) {
        ql_tap_state.state = cur_dance(state);
        switch (ql_tap_state.state) {
            case TD_SINGLE_TAP:
                if (host_keyboard_led_state().caps_lock) {
                    tap_code(KC_CAPS); // Disable caps if it's enabled
                }
                break;
            case TD_SINGLE_HOLD:
                break;
            case TD_DOUBLE_TAP:
                tap_code(KC_CAPS);
                break;
            case TD_DOUBLE_HOLD:
                layer_on(_SYSTEM);
                break;
        }
    }

    // Function that controls the reset tap dance
    void ql_reset(tap_dance_state_t *state, void *user_data) {
        // If the key was held down and now is released then switch off the layer
        if (ql_tap_state.state >= TD_DOUBLE_HOLD) {
            layer_off(_SYSTEM);
        }
        ql_tap_state.state = TD_NONE;
    }

    // Associate our tap dance key with its functionality
    tap_dance_action_t tap_dance_actions[] = {
        [TD_SYS_QL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),        // Caps lock/System layer dance
    };
#endif
//============Tap Dance Functions End================//

//============Post init code================//
void keyboard_post_init_user(void) {
    // Search for specific keys and replace on boot
    for (uint8_t layer = 0; layer < _LAYER_SAFE_RANGE; ++layer) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint16_t keycheck = keymap_key_to_keycode(layer, (keypos_t){col,row});

                switch(keycheck) {
                    case KC_CAPS:       // Replace KC_CAPS with tapdance version
                        #if defined(TAP_DANCE_ENABLE)
                            dynamic_keymap_set_keycode(layer, row, col, TD(0));
                        #endif
                        break;
                    case KC_BSLS:       // Replace KC_BSLS with VRSN on _SYSTEM layer
                            dynamic_keymap_set_keycode(_SYSTEM, row, col, VRSN);
                        break;
                    case RGB_MOD:       // Replace RGB_MOD with RGB_DEF on _SYSTEM layer
                            dynamic_keymap_set_keycode(_SYSTEM, row, col, RGB_DEF);
                        break;
                }
            }
        }
    }
    #ifdef CUSTOM_RGB_H
        keyboard_post_init_rgb();
    #endif
}
//============Post init code end============//

/*void suspend_power_down_user(void) {
    // code will run multiple times while keyboard is suspended
    suspend_power_down_rgb();
}

void suspend_wakeup_init_user(void) {
    // code will run on keyboard wakeup
    suspend_wakeup_init_rgb();
}*/

//============Userspace and keymap custom keycodes================//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPSOFF:    // Disable caps if it's enabled
            if (record->event.pressed) {
                if (host_keyboard_led_state().caps_lock) {
                    tap_code(KC_CAPS); // Disable caps if it's enabled
                }
            }
            return false;
        case KC_MAKE:       // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (record->event.pressed) {
                clear_mods();
                if (host_keyboard_led_state().caps_lock) tap_code(KC_CAPS); // Disable caps if it's enabled
                SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
                tap_code(KC_ENT);
            }
            return false;
        case VRSN:          // Prints QMK firmware version information
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
            }
            return false;
        default:
            #ifdef CUSTOM_RGB_H
                return process_record_rgb(keycode, record);
            #else
                return true;
            #endif
    }
}
//========Userspace and keymap custom keycodes end================//
