#ifndef TASKS_H
#define TASKS_H

#include <Arduino_FreeRTOS.h>
#include "configs.h"
#include "joystick.h"
#include "MedianFilter.h"
#include "dd_stdio.h"
#include "button_control.h"

void joystick_task_update(void *pvParameters);
void filters_task(void *pvParameters);
void report_task_run(void *pvParameters);
void tasks_init();

#endif
