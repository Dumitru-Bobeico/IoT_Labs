#include "joystick.h"

static double convert_raw_to_voltage(uint16_t raw_value)
{
    return ((double)raw_value / ADC_RESOLUTION) * ADC_REFERENCE;
}

static double convert_voltage_to_degree(double voltage)
{
    return ((voltage / ADC_REFERENCE) * (MAX_DEGREE - MIN_DEGREE)) + MIN_DEGREE;
}

void joystick_init(joystick_t *joystick,
                   uint8_t x_pin,
                   uint8_t y_pin,
                   uint8_t button_pin, 
                   int (*read_analog_func)(uint8_t),
                   uint8_t (*read_button_func)(uint8_t))
{
    if (joystick == NULL)
        return;

    joystick->x_pin = x_pin;
    joystick->y_pin = y_pin;
    joystick->button_pin = button_pin;
    joystick->x_raw_data = 0;
    joystick->y_raw_data = 0;
    joystick->x_degree = 0;
    joystick->y_degree = 0;
    joystick->is_pressed = 0;
    joystick->read_analog = read_analog_func;
    joystick->read_button = read_button_func;
}

void joystick_update(joystick_t *joystick)
{
    if (joystick == NULL)
        return;

    // Read analog joystick values
    joystick->x_raw_data = joystick->read_analog(joystick->x_pin);
    joystick->y_raw_data = joystick->read_analog(joystick->y_pin);

    // Convert to voltages
    double x_voltage = convert_raw_to_voltage(joystick->x_raw_data);
    double y_voltage = convert_raw_to_voltage(joystick->y_raw_data);

    // Convert voltages to degrees (-90° to +90°)
    joystick->x_degree = (int8_t)convert_voltage_to_degree(x_voltage);
    joystick->y_degree = (int8_t)convert_voltage_to_degree(y_voltage);

    // Read button state
    joystick->is_pressed = joystick->read_button(joystick->button_pin);
}

uint16_t joystick_get_x_raw(joystick_t *joystick)
{
    if (joystick == NULL)
        return 0;

    return joystick->x_raw_data;
}

uint16_t joystick_get_y_raw(joystick_t *joystick)
{
    if (joystick == NULL)
        return 0;

    return joystick->y_raw_data;
}

int8_t joystick_get_x_degree(joystick_t *joystick)
{
    if (joystick == NULL)
        return 0;

    return joystick->x_degree;
}

int8_t joystick_get_y_degree(joystick_t *joystick)
{
    if (joystick == NULL)
        return 0;

    return joystick->y_degree;
}

uint8_t joystick_is_button_pressed(joystick_t *joystick)
{
    if (joystick == NULL)
        return 0;

    return joystick->is_pressed;
}
