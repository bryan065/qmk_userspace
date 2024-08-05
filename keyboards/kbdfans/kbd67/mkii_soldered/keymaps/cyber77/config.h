#pragma once

#undef PRODUCT
#undef PRODUCT_ID
#undef BACKLIGHT_PIN

// Keyboard Settings
#define PRODUCT "Cyber77"
#define PRODUCT_ID 0x0014
#define CAPS_LED 3
#define NUMLK_LED 5

//Encoder pins
#ifdef ENCODER_ENABLE
    #define ENCODERS_PAD_A { B1 } // MISO
    #define ENCODERS_PAD_B { B3 } // SCLK / SCK
#endif

// RGB Matrix
#ifdef RGB_MATRIX_ENABLE
    #define WS2812_RGBW
    #define WS2812_DI_PIN B2
    #define RGB_MATRIX_LED_COUNT 76

    #define RGB_MATRIX_DEFAULT_SPD 64
    #define RGB_MATRIX_DEFAULT_HUE 170
    #define RGB_MATRIX_DEFAULT_SAT 255
    #define RGB_MATRIX_DEFAULT_VAL 150

    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_HUE_PENDULUM2
#endif
