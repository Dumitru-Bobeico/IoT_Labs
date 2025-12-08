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
    uint8_t pos = 0;

    printf("> "); fflush(stdout);

    while (1)
    {
        while (Serial.available())
        {
            char c = Serial.read();
            Serial.write(c); // echo

            if (c == '\r' || c == '\n') // command finished
            {
                input[pos] = '\0';
                pos = 0;

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
                else if (strlen(input) > 0) {
                    printf("\nUnknown command: %s\n", input);
                }

                printf("> "); fflush(stdout);
            }
            else
            {
                if (pos < sizeof(input)-1) {
                    input[pos++] = c;
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(CMD_TASK_DELAY_MS));
    }
}
