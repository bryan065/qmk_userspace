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
	[_BASE] = LAYOUT_all( /* Base */
		KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  KC_MUTE,
		KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_DEL,
		KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,        KC_CALC,
		KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   WIN_CPY,
		KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,  MO(_FUNCTION),           KC_SPC,    MO(_RGB), MO(_FUNCTION),          KC_LEFT, KC_DOWN, KC_RGHT
  	),

	[_FUNCTION] = LAYOUT_all( /* FN */
		KC_TILD,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______, KC_MPLY,
		 KC_GRV, _______, _______, _______, _______, _______, _______,   KC_P7,   KC_P8,   KC_P9, _______, _______, _______, WIN_VER, _______,
		_______, _______, _______, _______, _______, _______, _______,   KC_P4,   KC_P5,   KC_P6, _______, _______,          KC_PENT,          KC_MYCM,
		_______, _______, _______, _______, _______, _______, _______, _______,   KC_P1,   KC_P2,   KC_P3, _______,  KC_NUM,          KC_PGUP, KC_PSCR,
		_______, _______, _______,          _______,          _______,            KC_P0,          KC_PDOT, _______,          KC_HOME, KC_PGDN, KC_END
  	),

	[_RGB] = LAYOUT_all(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_SPI,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_VAI, RGB_SPD,
		_______, _______, _______,          _______,          _______,          _______,          _______, _______,          RGB_SAD, RGB_VAD, RGB_SAI
  	),

	[_SYSTEM] = LAYOUT_all(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLEP,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SCRL,          _______, _______,
		_______, _______, _______,          _______,          _______,          _______,          _______, _______,          _______, _______, _______
  	)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FUNCTION] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_RGB] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [_SYSTEM] = { ENCODER_CCW_CW(_______, _______) },
};
#endif

//========Keyboard & RGB matrix strip wiring / index====//
/*
*   ___________________________________
*  /   0          1  2  3  4  5  6     \_____________          <-- Light bar
* ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
* │ 7 │ 8 │ 9 │ 10│ 11│ 12│ 13│ 14│ 15│ 16│ 17│ 18│ 19│ 20    │21 │
* ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
* │ 36  │35 │34 │33 │32 │31 │30 │29 │28 │27 │26 │25 │24 │23   │22 │
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
* │ 37   │38 │39 │40 │41 │42 │43 │44 │45 │46 │47 │48 │  49    │50 │
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
* │ 64     │63 │62 │61 │60 │59 │58 │57 │56 │55 │54 │53    │51 │51 │
* ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
* │ 65 │ 66 │ 67 │  68      │ 69 │  70    │71 │72 │   │73 │74 │75 │
* └────┴────┴────┴──────────┴────┴────────┴───┴───┘   └───┴───┴───┘
*/


#ifdef RGB_MATRIX_ENABLE
//LED TO MATRIX MAP
led_config_t g_led_config = { {
        // Key Matrix to LED Index
        {      7,      8,      9,     10,     11,     12,     13,     14,     15, 16, 17, 18,     19,     20,     21 },
        {     36,     35,     34,     33,     32,     31,     30,     29,     28, 27, 26, 25,     24,     23,     22 },
        {     37,     38,     39,     40,     41,     42,     43,     44,     45, 46, 47, 48, NO_LED,     49,     50 },
        {     64,     63,     62,     61,     60,     59,     58,     57,     56, 55, 54, 53, NO_LED,     52,     51 },
        {     65,     66,     67,     68, NO_LED,     69, NO_LED,     70, NO_LED, 71, 72, 73, NO_LED,     74,     75 }
    }, {
        // LED Index to Physical Position **BASED ON KEY MATRIX TO LED INDEX (back and fourth snake in this case)
        {10,0},{50,0},{62,0},{74,0},{86,0},{98,0},{110,0},
        {0,12},{15,12},{30,12},{45,12},{60,12},{75,12},{90,12},{105,12},{120,12},{135,12},{150,12},{165,12},{180,12},{203,12},{224,12},
        {224,25},{203,25},{180,25},{165,25},{150,25},{135,25},{120,25},{105,25},{90,25},{75,25},{60,25},{45,25},{30,25},{15,25},{0,25},
        {0,38},{25,38},{40,38},{55,38},{70,38},{85,38},{100,38},{115,38},{130,38},{145,38},{160,38},{175,38},{201,38},{224,38},
        {224,51},{210,51},{189,51},{169,51},{154,51},{139,51},{120,51},{105,51},{90,51},{75,51},{60,51},{45,51},{25,51},{5,51},
        {2,64},{21,64},{39,64},{70,64},{90,64},{120,64},{150,64},{165,64},{190,64},{205,64},{224,64}
    }, {
        // LED Index to Flag
        2,2,2,2,2,2,2, // Lightbar
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 1,
        1, 1, 1,    1,    1,    1,    1, 1, 4, 4, 4,
    }
};
#endif
