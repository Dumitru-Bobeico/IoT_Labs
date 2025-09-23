#ifndef CONFIGS_H
#define CONFIGS_H

#include <Arduino.h>

#define COMMAND_MAX_LENGTH      10

#define ACTION_MAX_LENGTH       10

#define LED_PIN                 13

#define SERIAL_BAUD         115200

#define I2C_DISPLAY_ADDRESS     0x27
#define I2C_DISPLAY_COLUMNS     16
#define I2C_DISPLAY_ROWS        2

#define KEYPAD_ROWS             4
#define KEYPAD_COLS             4

enum KEYPAD_KEYS {
    KEYPAD_PIN_1 = 23,
    KEYPAD_PIN_2 = 25,
    KEYPAD_PIN_3 = 27,
    KEYPAD_PIN_4 = 29,
    KEYPAD_PIN_5 = 31,
    KEYPAD_PIN_6 = 33,
    KEYPAD_PIN_7 = 35,
    KEYPAD_PIN_8 = 37
};

#endif
