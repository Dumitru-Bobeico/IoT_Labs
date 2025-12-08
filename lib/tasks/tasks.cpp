#include "tasks.h"
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include "configs.h"
#include "relay.h"
#include "command_parser.h"
#include <stdio.h>

relay_t relay;

void relay_report_task(void* pvParameters) {
    (void) pvParameters;
    while (true) {
        printf("Relay state: %s\n", relay_get_state(&relay) ? "ON" : "OFF");
        vTaskDelay(pdMS_TO_TICKS(REPORT_TASK_DELAY_MS));
    }
}

void tasks_init() {
    relay_init(&relay, RELAY_PIN);

    xTaskCreate(command_parser_task, "CmdParser", 256, nullptr, 2, nullptr);
    xTaskCreate(relay_report_task, "RelayReport", 256, nullptr, 1, nullptr);
}
