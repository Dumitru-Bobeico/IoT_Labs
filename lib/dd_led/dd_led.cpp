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

void leds_init() {
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    green_led_off();
    red_led_off();
}
void green_led_on()  { digitalWrite(GREEN_LED_PIN, HIGH); }
void green_led_off() { digitalWrite(GREEN_LED_PIN, LOW);  }
void red_led_on()    { digitalWrite(RED_LED_PIN, HIGH); }
void red_led_off()   { digitalWrite(RED_LED_PIN, LOW);  }
