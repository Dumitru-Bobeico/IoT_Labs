    #include "button_control.h"

    void button_control_init(uint8_t pin) {
        pinMode(pin, INPUT_PULLUP);
    }

    uint8_t is_button_pressed(uint8_t pin) {
        return digitalRead(pin) == LOW;
    }
