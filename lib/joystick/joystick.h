#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define ADC_REFERENCE  5.0
#define ADC_RESOLUTION 1023.0
#define MAX_DEGREE     90.0
#define MIN_DEGREE    -90.0

typedef struct
{
    uint8_t x_pin;
    uint8_t y_pin;
    uint8_t button_pin;
    uint16_t x_raw_data;
    uint16_t y_raw_data;
    int8_t x_degree;
    int8_t y_degree;
    uint8_t is_pressed;

    int (*read_analog)(uint8_t pin);
    uint8_t (*read_button)(uint8_t pin);
} joystick_t;

// Initialization
void joystick_init(joystick_t *joystick,
                   uint8_t x_pin,
                   uint8_t y_pin,
                   uint8_t button_pin, 
                   int (*read_analog_func)(uint8_t),
                   uint8_t (*read_button_func)(uint8_t));

// Update all readings
void joystick_update(joystick_t *joystick);

// Getters
uint16_t joystick_get_x_raw(joystick_t *joystick);
uint16_t joystick_get_y_raw(joystick_t *joystick);

int8_t joystick_get_x_degree(joystick_t *joystick);
int8_t joystick_get_y_degree(joystick_t *joystick);

uint8_t joystick_is_button_pressed(joystick_t *joystick);

#endif // JOYSTICK_H
