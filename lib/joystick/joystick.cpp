#include "joystick.h"

static double convert_raw_to_voltage(uint16_t raw_value)
{
    return ((double)raw_value / ADC_RESOLUTION) * ADC_REFERENCE;
}

static double convert_voltage_to_degree(double voltage)
{
    return ((voltage / ADC_REFERENCE) * (MAX_DEGREE - MIN_DEGREE)) + MIN_DEGREE;
}

void joystick_init(joystick_t* joystick,
                   uint8_t x_pin,
                   uint8_t y_pin,
                   uint8_t button_pin,
                   int (*read_analog_func)(uint8_t),
                   uint8_t (*read_button_func)(uint8_t))
{
    if (!joystick) return;

    joystick->x_pin = x_pin;
    joystick->y_pin = y_pin;
    joystick->button_pin = button_pin;

    joystick->x_raw_data = 0;
    joystick->y_raw_data = 0;
    joystick->x_degree = 0;
    joystick->y_degree = 0;
    joystick->is_pressed = 0;

    joystick->filtered_x_raw = 0;
    joystick->filtered_y_raw = 0;

    joystick->read_analog = read_analog_func;
    joystick->read_button = read_button_func;
}

void joystick_update(joystick_t* joystick)
{
    if (!joystick) return;

    joystick->x_raw_data = (uint16_t)joystick->read_analog(joystick->x_pin);
    joystick->y_raw_data = (uint16_t)joystick->read_analog(joystick->y_pin);

    double x_voltage = convert_raw_to_voltage(joystick->x_raw_data);
    double y_voltage = convert_raw_to_voltage(joystick->y_raw_data);

    joystick->x_degree = (int8_t)convert_voltage_to_degree(x_voltage);
    joystick->y_degree = (int8_t)convert_voltage_to_degree(y_voltage);

    joystick->is_pressed = joystick->read_button(joystick->button_pin);
}

// ---------------- Getters ----------------
uint16_t joystick_get_x_raw(joystick_t* joystick) { return joystick ? joystick->x_raw_data : 0; }
uint16_t joystick_get_y_raw(joystick_t* joystick) { return joystick ? joystick->y_raw_data : 0; }
int8_t joystick_get_x_degree(joystick_t* joystick) { return joystick ? joystick->x_degree : 0; }
int8_t joystick_get_y_degree(joystick_t* joystick) { return joystick ? joystick->y_degree : 0; }
uint8_t joystick_is_button_pressed(joystick_t* joystick) { return joystick ? joystick->is_pressed : 0; }
