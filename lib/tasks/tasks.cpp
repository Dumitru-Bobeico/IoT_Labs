#include "tasks.h"

uint8_t g_first_led_state = LOW;
uint16_t g_second_led_frequency = 1;

void tasks_init(void) {
    timer_init_ISR_1KHz(TIMER_DEFAULT);
    pinMode(FIRST_LED, OUTPUT);
    pinMode(SECOND_LED, OUTPUT);
    button_control_init(ON_OFF_BUTTON_PIN);
    button_control_init(UP_BUTTON_PIN);
    button_control_init(DOWN_BUTTON_PIN);
}

void idle_task(void) {
    static uint32_t last_report = 0;
    uint32_t now = millis();

    if (now - last_report >= 500) {
        printf("First LED: %s | Second LED freq: %u Hz\r\n",
               g_first_led_state == HIGH ? "ON" : "OFF",
               g_second_led_frequency);
        last_report = now;
    }
}

void first_task(void) {
    static uint32_t next_check_time = 0;

    if (is_button_pressed(ON_OFF_BUTTON_PIN) && millis() > next_check_time) {
        g_first_led_state = !g_first_led_state;
        digitalWrite(FIRST_LED, g_first_led_state);
        next_check_time = millis() + DEBOUNCE_TIME_MS;
    }
}

void second_task(void) {
    static uint32_t last_toggle = 0;
    static uint8_t led_state = LOW;

    if (g_first_led_state == LOW) {
        if (g_second_led_frequency < 1) g_second_led_frequency = 1;
        uint32_t half_period = 1000UL / (g_second_led_frequency * 2UL);
        uint32_t now = millis();

        if (now - last_toggle >= half_period) {
            led_state = !led_state;
            digitalWrite(SECOND_LED, led_state);
            last_toggle = now;
        }
    } else {
        digitalWrite(SECOND_LED, LOW);
    }
}

void third_task(void) {
    static uint32_t next_check_time = 0;

    if (is_button_pressed(UP_BUTTON_PIN) && millis() > next_check_time) {
        if (g_second_led_frequency < 255) g_second_led_frequency++;
        next_check_time = millis() + DEBOUNCE_TIME_MS;
    }

    if (is_button_pressed(DOWN_BUTTON_PIN) && millis() > next_check_time) {
        if (g_second_led_frequency > 1) g_second_led_frequency--;
        next_check_time = millis() + DEBOUNCE_TIME_MS;
    }
}

void timer_handle_interrupts(int timer) {
    static uint32_t tick = 0;
    tick++;

    if (tick % FIRST_TASK_RECCURENCE_MS == 0) first_task();
    if (tick % SECOND_TASK_RECCURENCE_MS == 0) second_task();
    if (tick % THIRD_TASK_RECCURENCE_MS == 0) third_task();
}
