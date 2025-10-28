#include "dd_led.h"

void led_init_pin(int pin) {
    pinMode(pin, OUTPUT);
}

void led_set(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}

void led_toggle(int pin) {
    digitalWrite(pin, !digitalRead(pin));
}
