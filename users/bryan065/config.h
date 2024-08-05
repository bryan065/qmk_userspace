#pragma once

#undef DEBOUNCE

// Userspace Settings
#define FORCE_NKRO
#define DEBOUNCE 2
#define ENABLE_COMPILE_KEYCODE
#define USB_SUSPEND_WAKEUP_DELAY 200
#define USB_POLLING_INTERVAL_MS 1
#define NO_ACTION_ONESHOT

// Userspace RGB settings
#ifdef RGB_MATRIX_ENABLE
    #ifndef RGB_MATRIX_MAXIMUM_BRIGHTNESS
        #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
    #endif

    #define RGB_MATRIX_SLEEP
    #define RGB_MATRIX_TIMEOUT 300000

    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #define ENABLE_RGB_MATRIX_BREATHING
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #define ENABLE_RGB_MATRIX_RAINBOW_BEACON

    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#endif
