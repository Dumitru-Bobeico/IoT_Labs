#include <Arduino.h>
#include <tasks.h>
#include <dd_stdio.h>

void setup()
{
    Serial.begin(SERIAL_BAUD);
    stdio_init();
    tasks_init();
}

void loop()
{
    idle_task();
}
