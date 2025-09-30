#include "tasks.h"

static uint8_t first_led_state;
static uint8_t second_led_frequency;

void first_task_init(void) {
    first_led_state = LOW;
    led_control_init(FIRST_LED, OUTPUT);
    button_control_init(ON_OFF_BUTTON_PIN);
}

void first_task(void *pvParameters) {
    static uint8_t need_init = true;
    static uint32_t next_check_time = 0;

    if (need_init) {
        first_task_init();
        need_init = false;
    }

    if (is_button_pressed(ON_OFF_BUTTON_PIN)) {
        if (millis() > next_check_time) {
            led_control_toggle(FIRST_LED);
            first_led_state = !first_led_state;
            next_check_time = millis() + DEBOUNCE_TIME_MS; // debounce delay
        }
    }
}

void second_task_init(void) {
    second_led_frequency = SECOND_LED_BASE_FREQUENCY_MS;
    led_control_init(SECOND_LED, OUTPUT);

    
}

void second_task(void *pvParameters) {
    static uint8_t need_init = true;
    static uint32_t last_toggle_time = 0;

    if (need_init) {
        second_task_init();
        need_init = false;
        second_led_frequency = 1; // Start with 1 Hz
    }

    if (first_led_state == LOW) {
        uint32_t interval = 1000 / (second_led_frequency * 2); // Calculate interval based on frequency
        if (millis() - last_toggle_time >= interval) {
            led_control_toggle(SECOND_LED);
            last_toggle_time = millis();
        }
    } else {
        led_control_init(SECOND_LED, OUTPUT);
        led_control_toggle(SECOND_LED); // Ensure LED is off when first LED is off
    }
}


void third_task_init(void) {
    button_control_init(UP_BUTTON_PIN);
    button_control_init(DOWN_BUTTON_PIN);
}

void third_task(void *pvParameters) {
    static uint8_t need_init = true;
    static uint32_t next_check_time = 0;

    if (need_init) {
        third_task_init();
        need_init = false;
    }

    if (is_button_pressed(UP_BUTTON_PIN)) {
        if (millis() > next_check_time) {
            if (second_led_frequency > SECOND_LED_FREQUENCY_STEP_MS) { // Limit max frequency to 10 Hz
                second_led_frequency++;
            }
            next_check_time = millis() + DEBOUNCE_TIME_MS; // debounce delay
        }
    }

    if (is_button_pressed(DOWN_BUTTON_PIN)) {
        if (millis() > next_check_time) {
            if (second_led_frequency > 1) { // Limit min frequency to 1 Hz
                second_led_frequency--;
            }
            next_check_time = millis() + DEBOUNCE_TIME_MS; // debounce delay
        }
    }
}
