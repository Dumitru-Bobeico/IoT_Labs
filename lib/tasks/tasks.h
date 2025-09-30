#ifndef TASKS_H
#define TASKS_H

#include <timer-api.h>
#include "dd_led.h"
#include "button_control.h"
#include <configs.h>

void tasks_init();
void first_task(void *pvParameters);
void second_task(void *pvParameters);
void third_task(void *pvParameters);
void idle_task(void);

#endif