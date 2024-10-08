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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, _______, KC_BSPC,
        KC_TAB , KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, _______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(_FUNCTION), KC_SPC, LT(_RGB, KC_SCRL), MO(_FUNCTION), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_FUNCTION] = LAYOUT(
        KC_TILD , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7, KC_F8, KC_F9, KC_F10 , KC_F11 , KC_F12 , _______, KC_DEL,
        KC_GRV, _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, _______, _______, _______, WIN_CPY,
        _______ , _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, _______, _______, KC_PENT,
        _______ , _______, _______, _______, _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, _______, KC_NUM, KC_PGUP,
        _______ , _______, _______, _______, _______, KC_P0, _______, KC_PDOT, KC_HOME, KC_PGDN, KC_END
    ),
    [_RGB] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPI,
        _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_VAD, RGB_SAI
    ),
    [_SYSTEM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLEP,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


//========Keyboard & RGB matrix strip wiring / index====//
/* LED #75 to #99 is for underglow?
* #65 to 89 should be for underglow
*                                                                       Underglow
* ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐         ┌───────────────────────────────────────────────────────────┐
* │0  │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 10│ 11│ 12│ 13    │         │                                                           │
* ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤         │                                                           │
* │ 14  │15 │16 │17 │18 │19 │20 │21 │22 │23 │24 │25 │26 │27   │         │                                                           │
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤         │                                                           │
* │ 28   │29 │30 │31 │32 │33 │34 │35 │36 │37 │38 │39 │ 40     │         │                                                           │
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤         │                                                           │
* │ 41     │42 │43 │44 │45 │46 │47 │48 │49 │50 │51 │52    │53 │         │                                                           │
* ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤         │                                                           │
* │ 54 │ 55 │ 56 │  57      │ 58 │  59    │60 │61 │62 │63 │64 │         │                                                           │
* └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘         └───────────────────────────────────────────────────────────┘
*/

#ifdef RGB_MATRIX_ENABLE
//LED TO MATRIX MAP
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,      1,      2,      3,      4,      5,      6,      7,  8,      9, 10, 11,     12, NO_LED,     13 },
        { 14, NO_LED,     15,     16,     17,     18,     19,     20, 21,     22, 23, 24,     25,     26,     27 },
        { 28, NO_LED,     29,     30,     31,     32,     33,     34, 35,     36, 37, 38,     39,     40, NO_LED },
        { 41, NO_LED,     42,     43,     44,     45,     46,     47, 48,     49, 50, 51, NO_LED,     52,     53 },
        { 54,     55, NO_LED,     56,     57, NO_LED,     58, NO_LED, 59, NO_LED, 60, 61,     62,     63,     64 }
    }, {
        // LED Index to Physical Position
        {0,0} , {18,0} , {36,0} , {55,0} , {73,0} , {91,0} , {110,0} , {128,0} , {146,0} , {164,0} , {182,0} , {200,0} , {218,0} , {224,0} ,
        {0,16}, {18,16}, {36,16}, {55,16}, {73,16}, {91,16}, {110,16}, {128,16}, {146,16}, {164,16}, {182,16}, {200,16}, {218,16}, {224,16},
        {0,32}, {18,32}, {36,32}, {55,32}, {73,32}, {91,32}, {110,32}, {128,32}, {146,32}, {164,32}, {182,32}, {200,32}, {218,32},
        {0,48}, {18,48}, {36,48}, {55,48}, {73,48}, {91,48}, {110,48}, {128,48}, {146,48}, {164,48}, {182,48}, {200,48}, {218,48},
        {0,64}, {18,64}, {36,64}, {73,64}, {91,64},{110,64}, {146,64}, {164,64}, {182,64}, {200,64}, {218,64},
        //underglow
        {242,64}, {216,64}, {192,64}, {176,64}, {160,64}, {144,64}, {128,64}, {112,64}, {96,64}, {80,64}, {64,64}, {48,64}, {32,64}, {16,64}, {0,64},
        {0,16}, {16,16}, {32,16},                      {88,0}, {104,0}, {120,0}, {136,0},                               {176,16}, {192,16}, {216,16}
    }, {
        // LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 1, 1,     4,   1,    4, 1, 1, 1, 1, 1,
        // Underglow LED's
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
    }
};

#endif
