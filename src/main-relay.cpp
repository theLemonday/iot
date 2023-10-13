#include <Arduino.h>

const int relay = D5;

/*
 *  GPIO = D5 = IN
 *  DC- = GND
 *  DC+ = VIN
 *  COM -> NO | NC = neg
 */

void setup() {
    Serial.begin(115200);
    pinMode(relay, OUTPUT);
}

void loop() {
    // Normally Open configuration, send LOW signal to let current flow
    // (if you're usong Normally Closed configuration send HIGH signal)
    digitalWrite(relay, LOW);
    Serial.println("Current Flowing");
    delay(5000);

    // Normally Open configuration, send HIGH signal stop current flow
    // (if you're usong Normally Closed configuration send LOW signal)
    digitalWrite(relay, HIGH);
    Serial.println("Current not Flowing");
    delay(1000);
}