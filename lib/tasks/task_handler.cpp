#include "tasks.h"
#include <dd_stdio.h>

void tasks_init() {
    Serial.begin(SERIAL_BAUD);
    stdio_init(); // map printf to Serial

    // init hardware basics if needed
    led_init_pin(FIRST_LED);
    led_init_pin(SECOND_LED);

    // init timer ISR at 1 kHz (timer-api function)
    timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void timer_handle_interrupts(int timer) {
    static uint32_t tick = 0;
    tick++; // 1 ms tick

    // For each task we check (tick + offset) % recurrence == 0
    // Use constants from configs.h

    if (((tick + FIRST_TASK_OFFSET_MS) % FIRST_TASK_RECCURENCE_MS) == 0) {
        first_task(NULL);
    }

    if (((tick + SECOND_TASK_OFFSET_MS) % SECOND_TASK_RECCURENCE_MS) == 0) {
        second_task(NULL);
    }

    if (((tick + THIRD_TASK_OFFSET_MS) % THIRD_TASK_RECCURENCE_MS) == 0) {
        third_task(NULL);
    }
    
}