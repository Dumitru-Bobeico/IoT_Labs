#include <task.h>
#include <dd_stdio.h>

static joystick_t joystick;


void joystick_task_init(void)
{
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
    static TickType_t last_wake_time;

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

void report_task_init(void)
{
    stdio_init(BAUD_RATE);
}

void tasks_init()
{
    xTaskCreate(joystick_task, "Joystick Task", 128, NULL, 1, NULL);
    xTaskCreate(report_task, "Report Task", 128, NULL, 1, NULL);
}