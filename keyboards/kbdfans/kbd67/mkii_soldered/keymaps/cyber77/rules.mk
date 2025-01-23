# Features
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812

# Stock keyboard feature disable
BACKLIGHT_ENABLE = no

# Userspace code
USER_NAME := bryan065
INTROSPECTION_KEYMAP_C = bryan065.c
SRC +=  custom_rgb.c
