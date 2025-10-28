#include "tasks.h"
#include "configs.h"
#include "dd_led.h"
#include "button_control.h"
#include "dd_stdio.h"

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

// --- Global resources ---
SemaphoreHandle_t xButtonSemaphore;
QueueHandle_t xBufferQueue;
int N = 0;

// --- Task prototypes ---
void vTaskButtonLed(void *pvParameters);
void vTaskSincron(void *pvParameters);
void vTaskAsincron(void *pvParameters);

// --- Task 1: Button + LED ---
void vTaskButtonLed(void *pvParameters)
{
    static bool ledActive = false;
    static unsigned long ledOnTime = 0;

    for (;;)
    {
        if (is_button_pressed(ON_OFF_BUTTON_PIN))
        {
            led_set(FIRST_LED, true);
            ledActive = true;
            ledOnTime = millis();
            xSemaphoreGive(xButtonSemaphore);
        }

        if (ledActive && (millis() - ledOnTime >= LED_PRESSED_DURATION_MS))
        {
            led_set(FIRST_LED, false);
            ledActive = false;
        }

        vTaskDelay(pdMS_TO_TICKS(BUTTON_TASK_DELAY_MS));
    }
}

// --- Task 2: Sincron ---
void vTaskSincron(void *pvParameters)
{
    uint8_t buffer[50];

    for (;;)
    {
        if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE)
        {
            N++;
            if (N > 50) N = 1; // prevent overflow

            // Fill sequence 1..N
            for (int i = 0; i < N; i++)
                buffer[i] = i + 1;

            // Add zero terminator
            buffer[N] = 0;

            // Send to queue
            for (int i = 0; i <= N; i++)
                xQueueSend(xBufferQueue, &buffer[i], portMAX_DELAY);

            // Blink LED N times
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

    for (;;)
    {
        while (xQueueReceive(xBufferQueue, &byte, 0) == pdTRUE)
        {
            if (newSeries) {
                printf("\r\n[AsincronTask] Serie nouă: ");
                newSeries = false;
            }

            if (byte == 0) {
                printf("\r\n");
                newSeries = true;
            } else {
                printf("%d ", byte);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(ASINCRON_TASK_DELAY_MS));
    }
}


// --- Task initialization ---
void tasks_init()
{
    led_init_pin(FIRST_LED);
    led_init_pin(SECOND_LED);
    button_control_init(ON_OFF_BUTTON_PIN);

    // Create semaphore & queue
    xButtonSemaphore = xSemaphoreCreateBinary();
    xBufferQueue = xQueueCreate(64, sizeof(uint8_t));

    // Create tasks
    xTaskCreate(vTaskButtonLed, "ButtonLed", 256, NULL, 1, NULL);
    xTaskCreate(vTaskSincron, "Sincron", 256, NULL, 1, NULL);
    xTaskCreate(vTaskAsincron, "Asincron", 256, NULL, 1, NULL);

    vTaskStartScheduler();
}

void idle_task()
{
    vTaskDelay(pdMS_TO_TICKS(100));
}
