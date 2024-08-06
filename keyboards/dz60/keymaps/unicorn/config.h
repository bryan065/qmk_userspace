#pragma once

#undef PRODUCT
#undef PRODUCT_ID
#undef BACKLIGHT_PIN
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS

#define PRODUCT "DZ60 Unicorn"
#define PRODUCT_ID 0x2261

// RGB Matrix
#ifdef RGB_MATRIX_ENABLE
    #define WS2812_DI_PIN E2
    #define RGB_MATRIX_LED_COUNT 90
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 250

    #define RGB_MATRIX_DEFAULT_SPD 64
    #define RGB_MATRIX_DEFAULT_HUE 170
    #define RGB_MATRIX_DEFAULT_SAT 255
    #define RGB_MATRIX_DEFAULT_VAL 250

    //#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_HUE_PENDULUM2
#endif
