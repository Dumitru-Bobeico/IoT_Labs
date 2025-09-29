#include "dd_stdio.h"

static FILE serial_stdout;

LiquidCrystal_I2C lcd(I2C_DISPLAY_ADDRESS, I2C_DISPLAY_COLUMNS, I2C_DISPLAY_ROWS);

char keys[KEYPAD_ROWS][KEYPAD_COLS] = 
{
    {'1','2','3', 'A'},
    {'4','5','6', 'B'},
    {'7','8','9', 'C'},
    {'*','0','#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {KEYPAD_PIN_1, KEYPAD_PIN_2, KEYPAD_PIN_3, KEYPAD_PIN_4};
byte colPins[KEYPAD_COLS] = {KEYPAD_PIN_5, KEYPAD_PIN_6, KEYPAD_PIN_7, KEYPAD_PIN_8};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS );

int lcd_my_putchar(char c, FILE* f) {
    lcd.write(c);
    return c;
}

int keypad_my_getchar(FILE* f) {
    char key = NO_KEY;
    while (key == NO_KEY) {
        key = kpd.getKey();
    }
    return key;
}

void stdio_init() {
    lcd.init();
    lcd.backlight();

    fdev_setup_stream(&serial_stdout, lcd_my_putchar, keypad_my_getchar, _FDEV_SETUP_RW);
    stdin = stdout = &serial_stdout;
}
