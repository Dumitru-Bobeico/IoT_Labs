#include <Arduino.h>
#include "dd_stdio.h"
#include "tasks.h"
#include <configs.h>

void setup() {
    Serial.begin(SERIAL_BAUD);
    stdio_init();
    tasks_init();
}

void loop() {
}
