#include "tasks.h"

void task_init() {
    timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void timer_handle_interrupts(int timer) {
    uint32_t first_task_period_ms = FIRST_TASK_OFFSET_MS;
    uint32_t second_task_period_ms = SECOND_TASK_OFFSET_MS;
    uint32_t third_task_period_ms = THIRD_TASK_OFFSET_MS;
    
}