#include "dd_led.h"
#include "configs.h"

void led_init_pin(int pin) {
    pinMode(pin, OUTPUT);
}

void led_set(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}

void led_toggle(int pin) {
    digitalWrite(pin, !digitalRead(pin));
}

void led_control_init(const uint8_t pin, const uint8_t mode) {
    pinMode(pin, mode);
}
void led_control_toggle(const uint8_t pin) {
    digitalWrite(pin, !digitalRead(pin));
}