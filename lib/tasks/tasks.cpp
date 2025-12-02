#include "tasks.h"
#include "Arduino_FreeRTOS.h"
#include <stdio.h>

static joystick_t joystick;

static sMedianFilter_t medianFilterX;
static sMedianNode_t medianBufferX[NUM_ELEMENTS_MEDIAN_FILTER];

static sMedianFilter_t medianFilterY;
static sMedianNode_t medianBufferY[NUM_ELEMENTS_MEDIAN_FILTER];

// ---------------- Joystick Task ----------------
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

void joystick_task_update(void *pvParameters)
{
    static uint8_t need_init = 1;
    TickType_t last_wake_time = xTaskGetTickCount();

    if (need_init)
    {
        joystick_task_init();
        need_init = 0;
    }

    while (1)
    {
        joystick_update(&joystick);
        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(JOYSTICK_RECURENCE_MS));
    }
}

// ---------------- Filters Task ----------------
void filters_task_init(void)
{
    medianFilterX.numNodes = NUM_ELEMENTS_MEDIAN_FILTER;
    medianFilterX.medianBuffer = medianBufferX;
    MEDIANFILTER_Init(&medianFilterX);

    medianFilterY.numNodes = NUM_ELEMENTS_MEDIAN_FILTER;
    medianFilterY.medianBuffer = medianBufferY;
    MEDIANFILTER_Init(&medianFilterY);
}

void filters_task(void *pvParameters)
{
    static uint8_t need_init = 1;
    TickType_t last_wake_time = xTaskGetTickCount();

    if (need_init)
    {
        filters_task_init();
        need_init = 0;
    }

    while (1)
    {
        // Apply median filter
        joystick.filtered_x_raw = MEDIANFILTER_Insert(&medianFilterX, joystick.x_raw_data);
        joystick.filtered_y_raw = MEDIANFILTER_Insert(&medianFilterY, joystick.y_raw_data);

        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(JOYSTICK_RECURENCE_MS));
    }
}

// ---------------- Report Task ----------------
void report_task_init(void)
{
    stdio_init();
}

void report_task_run(void *pvParameters)
{
    static uint8_t need_init = 1;
    static uint32_t time_ms = 0;
    TickType_t last_wake_time = xTaskGetTickCount();

    if (need_init)
    {
        report_task_init();
        need_init = 0;
    }

    while (1)
    {
        printf("Time: %lu ms\r\n", time_ms);
        printf("Joystick X deg: %d\r\n", joystick_get_x_degree(&joystick));
        printf("Joystick Y deg: %d\r\n", joystick_get_y_degree(&joystick));
        printf("Joystick X raw: %u (filtered: %d)\r\n", joystick_get_x_raw(&joystick), joystick.filtered_x_raw);
        printf("Joystick Y raw: %u (filtered: %d)\r\n", joystick_get_y_raw(&joystick), joystick.filtered_y_raw);

        printf("Button state  : %s\r\n\r\n", joystick_is_button_pressed(&joystick) ? "Pressed" : "Released");


        time_ms += REPORT_RECURRENCE_MS;
        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(REPORT_RECURRENCE_MS));
    }
}

// ---------------- Tasks Init ----------------
void tasks_init()
{
    xTaskCreate(joystick_task_update, "Joystick Task", 256, NULL, 1, NULL);
    xTaskCreate(filters_task, "Filters Task", 256, NULL, 1, NULL);
    xTaskCreate(report_task_run, "Report Task", 512, NULL, 1, NULL);
}
