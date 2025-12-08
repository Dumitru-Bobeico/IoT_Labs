#include "relay.h"
#include <Arduino.h>

void relay_init(relay_t *r, uint8_t pin) {
    r->pin = pin;
    r->state = 0;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void relay_set_state(relay_t *r, uint8_t state) {
    r->state = state ? 1 : 0;
    digitalWrite(r->pin, r->state ? HIGH : LOW);
}

uint8_t relay_get_state(relay_t *r) {
    return r->state;
}
