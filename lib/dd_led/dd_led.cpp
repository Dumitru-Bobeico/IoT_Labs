#include "dd_led.h"
#include "configs.h"

void led_init() {
    pinMode(LED_PIN, OUTPUT);
}

void led_on() {
    digitalWrite(LED_PIN, HIGH);
}

void led_off() {
    digitalWrite(LED_PIN, LOW);
}

void led_blink(void)
{
    for (int i = 0; i < 5; i++) // while (1) for infinite
    {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
}
