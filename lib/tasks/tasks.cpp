#include "tasks.h"

uint8_t g_first_led_state = LOW;
uint16_t g_second_led_frequency = 1;

uint32_t g_idle_last_report = 0;
uint32_t g_first_next_check_time = 0;
uint32_t g_second_last_toggle = 0;
uint8_t  g_second_led_state = LOW;
uint32_t g_third_next_check_time = 0;
uint32_t g_tick = 0;


void tasks_init(void) {
    timer_init_ISR_1KHz(TIMER_DEFAULT);
    pinMode(FIRST_LED, OUTPUT);
    pinMode(SECOND_LED, OUTPUT);
    button_control_init(ON_OFF_BUTTON_PIN);
    button_control_init(UP_BUTTON_PIN);
    button_control_init(DOWN_BUTTON_PIN);
}

void idle_task(void) {
    uint32_t now = millis();
    if (now - g_idle_last_report >= 500) {
        printf("First LED: %s | Second LED freq: %u Hz\r\n", g_first_led_state == HIGH ? "ON" : "OFF", g_second_led_frequency);
        g_idle_last_report = now;
    }
}

void first_task(void) {
    if (is_button_pressed(ON_OFF_BUTTON_PIN) && millis() > g_first_next_check_time) {
        g_first_led_state = !g_first_led_state;
        digitalWrite(FIRST_LED, g_first_led_state);
        g_first_next_check_time = millis() + DEBOUNCE_TIME_MS;
    }
}


void second_task(void) {
    if (g_first_led_state == LOW) {
        if (g_second_led_frequency < 1) g_second_led_frequency = 1;
        uint32_t half_period = 1000 / (g_second_led_frequency * 2);
        uint32_t now = millis();

        if (now - g_second_last_toggle >= half_period) {
            g_second_led_state = !g_second_led_state;
            digitalWrite(SECOND_LED, g_second_led_state);
            g_second_last_toggle = now;
        }
    } else {
        g_second_led_state = LOW;
        digitalWrite(SECOND_LED, LOW);
    }
}


void third_task(void) {
    if (is_button_pressed(UP_BUTTON_PIN) && millis() > g_third_next_check_time) {
        g_second_led_frequency++;
        g_third_next_check_time = millis() + DEBOUNCE_TIME_MS;
    }

    if (is_button_pressed(DOWN_BUTTON_PIN) && millis() > g_third_next_check_time) {
        if (g_second_led_frequency > 1) g_second_led_frequency--;
        g_third_next_check_time = millis() + DEBOUNCE_TIME_MS;
    }
}

void timer_handle_interrupts(int timer) {
    g_tick++;

    if (g_tick % FIRST_TASK_RECCURENCE_MS == FIRST_TASK_OFFSET_MS) first_task();
    if (g_tick % SECOND_TASK_RECCURENCE_MS == SECOND_TASK_OFFSET_MS) second_task();
    if (g_tick % THIRD_TASK_RECCURENCE_MS == THIRD_TASK_OFFSET_MS) third_task();
}

