#include "command_parser.h"
#include "relay.h"
#include "configs.h"
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Arduino.h>
#include <string.h>
#include <stdio.h>

// external relay object
extern relay_t relay;

void command_parser_task(void *pvParameters)
{
    (void) pvParameters;
    char input[32];

    while (1)
    {
        printf("> ");   // print prompt
        fflush(stdout);

        scanf("%31s", input); // read one word from STDIO (your typed command)

        if (strcmp(input, "on") == 0) {
            relay_set_state(&relay, 1);
            printf("\nRelay turned ON\n");
        }
        else if (strcmp(input, "off") == 0) {
            relay_set_state(&relay, 0);
            printf("\nRelay turned OFF\n");
        }
        else if (strcmp(input, "status") == 0) {
            printf("\nRelay state: %s\n", relay_get_state(&relay) ? "ON" : "OFF");
        }
        else {
            printf("\nUnknown command: %s\n", input);
        }

        vTaskDelay(pdMS_TO_TICKS(CMD_TASK_DELAY_MS));
    }
}

