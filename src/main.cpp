#include <Arduino.h>
#include "commands.h"
#include "dd_stdio.h"

void setup()
{
    commands_init();
    
}

void loop()
{
    char ch = 0;
    scanf("%c", &ch);
    printf("%c", ch);
}
