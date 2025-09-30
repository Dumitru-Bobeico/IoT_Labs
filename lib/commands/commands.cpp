#include "commands.h"
#include "dd_led.h"
#include "dd_stdio.h"
#include "configs.h"
#include <stdio.h>
#include <string.h>

void commands_init(void)
{
    led_init_pin(GREEN_LED_PIN);
    led_init_pin(RED_LED_PIN);

    stdio_init();
}

void commands_check_pin()
{
    char pin[5];
    int index = 0;
    char key;

    lcd.clear();
    printf("Enter PIN: ");

    while (1)
    {
        key = getchar();
        if (key != NO_KEY)
        {
            if (key == '#')
            {
                pin[index] = '\0';
                break;
            }
            else if (index < 4 && key >= '0' && key <= '9')
            {
                pin[index++] = key;
                printf("*");
            }
        }
    }

    lcd.clear();
    if (strcmp(pin, ACCESS_PIN) == 0)
    {
        led_set(GREEN_LED_PIN, true);
        led_set(RED_LED_PIN, false);
        printf("Correct");
    }
    else
    {
        led_set(RED_LED_PIN, true);
        led_set(GREEN_LED_PIN, false);
        printf("Wrong");
    }

    delay(3000);

    led_set(GREEN_LED_PIN, false);
    led_set(RED_LED_PIN, false);
    lcd.clear();
}
