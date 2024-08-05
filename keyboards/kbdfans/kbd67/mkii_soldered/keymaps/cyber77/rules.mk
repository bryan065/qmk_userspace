# Features
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812

# Stock keyboard feature disable
BACKLIGHT_ENABLE = no

USER_NAME := bryan065
SRC += \
	bryan065.c \
	custom_rgb.c
