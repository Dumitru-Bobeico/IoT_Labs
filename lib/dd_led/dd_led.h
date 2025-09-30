#ifndef DD_LED_H
#define DD_LED_H

#include <Arduino.h>

void led_init_pin(int pin);

void led_set(int pin, bool state);

void led_toggle(int pin);

#endif
