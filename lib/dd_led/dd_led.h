#ifndef DD_LED_H
#define DD_LED_H

#include <Arduino.h>

void led_init();

void led_on();
void led_off();
void led_blink();

void leds_init();
void green_led_on();
void green_led_off();
void red_led_on();
void red_led_off();

#endif