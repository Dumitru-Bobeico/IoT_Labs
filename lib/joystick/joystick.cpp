#include "joystick.h"
#include <math.h>

static int8_t convert_to_degree(uint16_t raw_value)
{
    float normalized = ((float)raw_value / ADC_RESOLUTION) * 2.0 - 1.0;
    float degree = normalized * MAX_DEGREE;
    if (degree > MAX_DEGREE) degree = MAX_DEGREE;
    if (degree < MIN_DEGREE) degree = MIN_DEGREE;
    return (int8_t)degree;
}

void joystick_init(joystick_t *joystick,
                   uint8_t x_pin,
                   uint8_t y_pin,
                   uint8_t button_pin, 
                   int (*read_analog_func)(uint8_t),
                   uint8_t (*read_button_func)(uint8_t))
{
    joystick->x_pin = x_pin;
    joystick->y_pin = y_pin;
    joystick->button_pin = button_pin;
    joystick->read_analog = read_analog_func;
    joystick->read_button = read_button_func;
}

void joystick_update(joystick_t *joystick)
{
    joystick->x_raw_data = joystick->read_analog(joystick->x_pin);
    joystick->y_raw_data = joystick->read_analog(joystick->y_pin);
    joystick->x_degree = convert_to_degree(joystick->x_raw_data);
    joystick->y_degree = convert_to_degree(joystick->y_raw_data);
    joystick->is_pressed = joystick->read_button(joystick->button_pin);
}

uint16_t joystick_get_x_raw(joystick_t *joystick)
{
    return joystick->x_raw_data;
}

uint16_t joystick_get_y_raw(joystick_t *joystick)
{
    return joystick->y_raw_data;
}

int8_t joystick_get_x_degree(joystick_t *joystick)
{
    return joystick->x_degree;
}

int8_t joystick_get_y_degree(joystick_t *joystick)
{
    return joystick->y_degree;
}

uint8_t joystick_is_button_pressed(joystick_t *joystick)
{
    return joystick->is_pressed;
}
