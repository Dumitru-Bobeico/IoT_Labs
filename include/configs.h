#ifndef CONFIGS_H
#define CONFIGS_H

#include <Arduino.h>

#define COMMAND_MAX_LENGTH      10

#define ACTION_MAX_LENGTH       10

#define LED_PIN                 13

#define SERIAL_BAUD             115200

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

#define RED_LED_PIN             54
#define GREEN_LED_PIN           57
#define ACCESS_PIN              "1234"

#define FIRST_LED               13
#define SECOND_LED              12
#define ON_OFF_BUTTON_PIN       10
#define UP_BUTTON_PIN           9
#define DOWN_BUTTON_PIN         8  
#define DEBOUNCE_TIME_MS        200

#define SECOND_LED_BASE_FREQUENCY_MS 1
#define SECOND_LED_FREQUENCY_STEP_MS 1
#define FIRST_TASK_OFFSET_MS        1
#define FIRST_TASK_RECCURENCE_MS    10

#define SECOND_TASK_OFFSET_MS   5
#define SECOND_TASK_RECCURENCE_MS   10

#define THIRD_TASK_OFFSET_MS    10
#define THIRD_TASK_RECCURENCE_MS    50

#endif
