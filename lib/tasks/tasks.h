#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void tasks_init();
void idle_task();
void joystick_task(void *pvParameters);


#endif
