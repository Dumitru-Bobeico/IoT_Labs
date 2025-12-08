#include <Arduino.h>
#include "dd_stdio.h"
#include "tasks.h"
#include "configs.h"

void setup() {
    Serial.begin(SERIAL_BAUD);

    // enable printf / scanf
    stdio_init();

    // initialize RTOS tasks
    tasks_init();
}

void loop() {
    // FreeRTOS runs the tasks
}
