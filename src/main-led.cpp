#include <Arduino.h>

const int LED_PIN = D4;
int dutyCycle = 0;

void setup() {
}

void loop() {
    for (; dutyCycle < 255; dutyCycle++) {
        analogWrite(LED_PIN, dutyCycle);
        delay(50);
    }

    for (; dutyCycle >= 0; dutyCycle--) {
        analogWrite(LED_PIN, dutyCycle);
        delay(50);
    }
}