#include "tasks.h"
#include "configs.h"
#include "dd_led.h"
#include "button_control.h"
#include "dd_stdio.h"

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

SemaphoreHandle_t xButtonSemaphore;
SemaphoreHandle_t xMutex;
QueueHandle_t xBufferQueue;
int N = 0;

void vTaskButtonLed(void *pvParameters);
void vTaskSincron(void *pvParameters);
void vTaskAsincron(void *pvParameters);

void vTaskButtonLed(void *pvParameters)
{
    static bool ledActive = false;
    static unsigned long ledOnTime = 0;
    static bool buttonPrevState = false;
    static unsigned long lastPressTime = 0;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(10);

    for (;;)
    {
        bool pressed = is_button_pressed(ON_OFF_BUTTON_PIN);

        if (pressed && !buttonPrevState && (millis() - lastPressTime > 200))
        {
            lastPressTime = millis();
            led_set(FIRST_LED, true);
            ledActive = true;
            ledOnTime = millis();

            xSemaphoreGive(xButtonSemaphore);
            printf("[Task 1] Semaphore given\r\n");
        }

        buttonPrevState = pressed;

        if (ledActive && (millis() - ledOnTime >= LED_PRESSED_DURATION_MS))
        {
            led_set(FIRST_LED, false);
            ledActive = false;
        }

        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void vTaskSincron(void *pvParameters)
{
    uint8_t buffer[50];

    for (;;)
    {
        if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("[Task 2] Semaphore detected\r\n");

            xSemaphoreTake(xMutex, portMAX_DELAY);
            N++;
            if (N > 50) N = 1;
            xSemaphoreGive(xMutex);

            for (int i = 0; i < N; i++)
                buffer[i] = i + 1;
            buffer[N] = 0;

            for (int i = 0; i <= N; i++)
                xQueueSendToFront(xBufferQueue, &buffer[i], portMAX_DELAY);

            printf("[Task 2] Queue sent\r\n");

            for (int i = 0; i < N; i++)
            {
                led_set(SECOND_LED, true);
                vTaskDelay(pdMS_TO_TICKS(LED_ON_MS));
                led_set(SECOND_LED, false);
                vTaskDelay(pdMS_TO_TICKS(LED_OFF_MS));
            }
        }

        vTaskDelay(pdMS_TO_TICKS(SINCRON_TASK_DELAY_MS));
    }
}

void vTaskAsincron(void *pvParameters)
{
    uint8_t byte;
    static bool newSeries = true;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(ASINCRON_TASK_DELAY_MS);

    for (;;)
    {
        while (xQueueReceive(xBufferQueue, &byte, 0) == pdTRUE)
        {
            if (newSeries)
            {
                printf("\r\n[Task 3] Serie noua: ");
                newSeries = false;
            }

            if (byte == 0)
            {
                printf("\r\n");
                newSeries = true;
            }
            else
            {
                printf("%d ", byte);
            }
        }

        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void tasks_init()
{
    led_init_pin(FIRST_LED);
    led_init_pin(SECOND_LED);
    button_control_init(ON_OFF_BUTTON_PIN);

    xButtonSemaphore = xSemaphoreCreateBinary();
    xMutex = xSemaphoreCreateMutex();
    xBufferQueue = xQueueCreate(64, sizeof(uint8_t));

    xTaskCreate(vTaskButtonLed, "ButtonLed", 256, NULL, 1, NULL);
    xTaskCreate(vTaskSincron, "Sincron", 256, NULL, 1, NULL);
    xTaskCreate(vTaskAsincron, "Asincron", 256, NULL, 1, NULL);

    vTaskStartScheduler();
}

void idle_task()
{
    vTaskDelay(pdMS_TO_TICKS(100));
}
