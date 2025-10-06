#ifndef TASKS_H
#define TASKS_H

#include <timer-api.h>
#include "dd_led.h"
#include "button_control.h"
#include <configs.h>

void tasks_init(void);
void first_task(void);
void second_task(void);
void third_task(void);
void idle_task(void);

void timer_handle_interrupts(int timer);

#endif