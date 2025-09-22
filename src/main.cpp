#include <Arduino.h>
#include "commands.h"

void setup()
{
    commands_init();
}

void loop()
{
    commands_process();
}
