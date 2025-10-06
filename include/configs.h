#ifndef CONFIGS_H
#define CONFIGS_H

#include <Arduino.h>

#define COMMAND_MAX_LENGTH              10

#define ACTION_MAX_LENGTH               10

#define LED_PIN                         13

#define SERIAL_BAUD                     115200

#define RED_LED_PIN                     54
#define GREEN_LED_PIN                   57

#define FIRST_LED                       13
#define SECOND_LED                      12
#define ON_OFF_BUTTON_PIN               10
#define UP_BUTTON_PIN                   9
#define DOWN_BUTTON_PIN                 8  
#define DEBOUNCE_TIME_MS                200

#define SECOND_LED_BASE_FREQUENCY_MS    1
#define SECOND_LED_FREQUENCY_STEP_MS    1
#define FIRST_TASK_OFFSET_MS            1
#define FIRST_TASK_RECCURENCE_MS        10

#define SECOND_TASK_OFFSET_MS           5
#define SECOND_TASK_RECCURENCE_MS       10

#define THIRD_TASK_OFFSET_MS            10
#define THIRD_TASK_RECCURENCE_MS        50

#endif
