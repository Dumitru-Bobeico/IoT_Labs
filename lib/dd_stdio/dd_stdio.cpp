#include "dd_stdio.h"

static FILE serial_stdout;

int my_putchar(char c, FILE* f) {
    Serial.write(c);
    return 0;
}

int my_getchar(FILE* f) {
    while (!Serial.available());
    char c = Serial.read();
    Serial.write(c);
    return c;
}

void stdio_init() {
    fdev_setup_stream(&serial_stdout, my_putchar, my_getchar, _FDEV_SETUP_RW);
    stdin = stdout = &serial_stdout;
}
