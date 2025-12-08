#include <Arduino.h>
#include "dd_stdio.h"
#include "tasks.h"
#include "configs.h"

void setup() {
    Serial.begin(SERIAL_BAUD);
    stdio_init(); // enable printf/scanf
    tasks_init();
}

void loop() {
    // FreeRTOS runs the tasks
}
