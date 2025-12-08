#ifndef RELAY_H
#define RELAY_H

#include <stdint.h>

typedef struct {
    uint8_t pin;
    uint8_t state; // 0 = OFF, 1 = ON
} relay_t;

void relay_init(relay_t *r, uint8_t pin);
void relay_set_state(relay_t *r, uint8_t state);
uint8_t relay_get_state(relay_t *r);

#endif
