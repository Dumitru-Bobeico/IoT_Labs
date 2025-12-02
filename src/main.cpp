#include <Arduino.h>
#include "tasks.h"

void setup()
{
    Serial.begin(BAUDRATE);
    tasks_init();
    vTaskStartScheduler();
}

void loop()
{
    // Empty: RTOS handles tasks
}
