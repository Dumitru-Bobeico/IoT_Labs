#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <dd_stdio.h>
#include "joystick.h"
#include "configs.h"
#include "button_control.h"

static joystick_t joystick;

void joystick_task_init(void)
{
    button_control_init(JOYSTICK_BUTTON_PIN);
    joystick_init(&joystick,
                  JOYSTICK_X_PIN,
                  JOYSTICK_Y_PIN,
                  JOYSTICK_BUTTON_PIN,
                  analogRead,
                  is_button_pressed);
}

void joystick_task(void *pvParameters)
{
    static uint8_t need_init = true;
    TickType_t last_wake_time = xTaskGetTickCount();

    if (need_init)
    {
        joystick_task_init();
        need_init = false;
    }

    while (true)
    {
        joystick_update(&joystick);
        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(JOYSTICK_RECCURENCE_MS));
    }
}

void report_task(void *pvParameters)
{
    static TickType_t last_report_time = 0;
    const TickType_t report_interval = pdMS_TO_TICKS(REPORT_RECCURENCE_MS);

    while (true)
    {
        if (xTaskGetTickCount() - last_report_time > report_interval)
        {
            printf("X: %d, Y: %d\r\n", joystick_get_x_degree(&joystick), joystick_get_y_degree(&joystick));
            last_report_time = xTaskGetTickCount();
        }

        if (joystick_is_button_pressed(&joystick))
        {
            printf("joystick pressed\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(50)); // Poll for button press every 50ms
    }
}

void report_task_init(void)
{
    stdio_init();
}

void tasks_init()
{
    xTaskCreate(joystick_task, "Joystick Task", 128, NULL, 1, NULL);
    xTaskCreate(report_task, "Report Task", 128, NULL, 1, NULL);
}
