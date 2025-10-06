#include "tasks.h"

volatile uint8_t g_first_led_state = LOW;
volatile uint16_t g_second_led_frequency = 1;

void idle_task(void)
{
    static uint32_t last_report = 0;
    uint32_t now = millis();

    if (now - last_report >= 500) {
        noInterrupts();
        uint8_t first_state = g_first_led_state;
        uint16_t freq = g_second_led_frequency;
        interrupts();

        printf("First LED: %s | Second LED freq: %u Hz\r\n",
               first_state == HIGH ? "ON" : "OFF",
               (unsigned)freq);
        last_report = now;
    }
}

/* --------------------
   TASK 1: Button LED
   -------------------- */
static void first_task_init(void)
{
    led_control_init(FIRST_LED, OUTPUT);
    button_control_init(ON_OFF_BUTTON_PIN);
    noInterrupts();
    g_first_led_state = LOW;
    interrupts();
}

void first_task(void *pvParameters)
{
    static uint8_t need_init = 1;
    static uint32_t next_check_time = 0;

    if (need_init) {
        first_task_init();
        need_init = 0;
    }

    if (is_button_pressed(ON_OFF_BUTTON_PIN)) {
        if (millis() > next_check_time) {
            noInterrupts();
            if (g_first_led_state == LOW) {
                g_first_led_state = HIGH;
                digitalWrite(FIRST_LED, HIGH);
            } else {
                g_first_led_state = LOW;
                digitalWrite(FIRST_LED, LOW);
            }
            interrupts();

            next_check_time = millis() + DEBOUNCE_TIME_MS;
        }
    }
}

/* --------------------
   TASK 2: Blinking LED
   -------------------- */
static void second_task_init(void)
{
    led_control_init(SECOND_LED, OUTPUT);
    noInterrupts();
    g_second_led_frequency = SECOND_LED_BASE_FREQUENCY_MS;
    interrupts();
}

void second_task(void *pvParameters)
{
    static uint8_t need_init = 1;
    static uint32_t last_toggle = 0;
    static uint8_t led_state = LOW;

    if (need_init) {
        second_task_init();
        need_init = 0;
    }

    noInterrupts();
    uint8_t first_state = g_first_led_state;
    uint16_t freq = g_second_led_frequency;
    interrupts();

    if (first_state == LOW) {
        if (freq == 0) freq = 1;
        uint32_t half_period = 1000UL / (freq * 2UL);
        uint32_t now = millis();
        if (now - last_toggle >= half_period) {
            led_state = !led_state;
            digitalWrite(SECOND_LED, led_state ? HIGH : LOW);
            last_toggle = now;
        }
    } else {
        led_state = LOW;
        digitalWrite(SECOND_LED, LOW);
    }
}

/* --------------------
   TASK 3: Buttons to adjust frequency
   -------------------- */
static void third_task_init(void)
{
    button_control_init(UP_BUTTON_PIN);
    button_control_init(DOWN_BUTTON_PIN);
    noInterrupts();
    if (g_second_led_frequency < 1) g_second_led_frequency = 1;
    interrupts();
}

void third_task(void *pvParameters)
{
    static uint8_t need_init = 1;
    static uint32_t next_check_time = 0;

    if (need_init) {
        third_task_init();
        need_init = 0;
    }

    if (is_button_pressed(UP_BUTTON_PIN)) {
        if (millis() > next_check_time) {
            noInterrupts();
            if (g_second_led_frequency < 255) g_second_led_frequency++;
            interrupts();

            next_check_time = millis() + DEBOUNCE_TIME_MS;
        }
    }

    if (is_button_pressed(DOWN_BUTTON_PIN)) {
        if (millis() > next_check_time) {
            noInterrupts();
            if (g_second_led_frequency > 1) g_second_led_frequency--;
            interrupts();

            next_check_time = millis() + DEBOUNCE_TIME_MS;
        }
    }
}