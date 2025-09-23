#include "commands.h"
#include "dd_led.h"
#include "dd_stdio.h"
#include "configs.h"
#include <stdio.h>

void commands_init(void)
{
    led_init();
    Serial.begin(SERIAL_BAUD);
    while (!Serial);

    stdio_init();

}

void commands_process(void)
{
    char command[COMMAND_MAX_LENGTH];
    char action[ACTION_MAX_LENGTH];

    printf("Enter command: ");
    scanf("%19s", command);

    if (strcmp(command, "led") == 0)
    {
        scanf("%9s", action);

        if (strcmp(action, "on") == 0)
        {
            led_on();
            printf("LED turned on\r\n");
        }
        else if (strcmp(action, "off") == 0)
        {
            led_off();
            printf("LED turned off\r\n");
        }
        else if (strcmp(action, "blink") == 0)
        {
            led_blink();
            printf("LED is blinking\r\n");
        }
        else
        {
            printf("Unknown action: %s\r\n", action);
        }

        return;
    }

    printf("Unknown command: %s\r\n", command);
}
