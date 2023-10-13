#include <Arduino.h>

const int LED_PIN = LED_BUILTIN;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);

    delay(1000);

    digitalWrite(LED_PIN, LOW);

    delay(200);
}