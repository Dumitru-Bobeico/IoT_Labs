#include <Arduino.h>
#include <tasks.h>

void setup()
{
    tasks_init();
}

void loop()
{
    idle_task();
}
