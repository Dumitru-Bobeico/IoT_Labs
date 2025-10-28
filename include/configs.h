#ifndef CONFIGS_H
#define CONFIGS_H

#include <Arduino.h>

#define FIRST_LED                   13
#define SECOND_LED                  12
#define ON_OFF_BUTTON_PIN           10

#define SERIAL_BAUD                 115200

// Task timings
#define BUTTON_TASK_DELAY_MS        10
#define SINCRON_TASK_DELAY_MS       50
#define ASINCRON_TASK_DELAY_MS      200

// LED blink durations
#define LED_ON_MS                   300
#define LED_OFF_MS                  500
#define LED_PRESSED_DURATION_MS     1000

#endif
