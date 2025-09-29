#include "commands.h"
#include "dd_led.h"
#include "dd_stdio.h"
#include "configs.h"
#include <stdio.h>
#include <string.h>

void commands_init(void)
{
    leds_init();
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
    if (strcmp(pin, "1234") == 0)
    {
        green_led_on();
        red_led_off();
        printf("Correct");
    }
    else
    {
        red_led_on();
        green_led_off();
        printf("Wrong");
    }

    delay(3000);
    green_led_off();
    red_led_off();
    lcd.clear();
}
