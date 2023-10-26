#include <Arduino.h>
#include <Constant.h>
#include <BlynkSimpleEsp8266.h>
#include <Sensor.h>
#include <Relay.h>

BlynkTimer timer;
MoistureSensor moistureSensor(A0, D0);
Sensor MQ2(A0, D2);
Relay pumpRelay(D1);

void myTimer() {
    int temperature = moistureSensor.readMoisturePercentage();
    Blynk.virtualWrite(V0, temperature);

    if (moistureSensor.isAboveThreshold() || MQ2.isAboveThreshold()) {
        Blynk.virtualWrite(V1, LOW);
        pumpRelay.on();
        Serial.println("Turn on the motor");
    } else {
        Blynk.virtualWrite(V1, HIGH);
        Serial.println("Turn off the motor");
        pumpRelay.off();
    }
}

void setup() {
    Serial.begin(BAUD_RATE);

    timer.setInterval(2000L, myTimer);
    Blynk.begin(BLYNK_AUTH_TOKEN, SSID, WIFI_PASSWORD);
}

BLYNK_CONNECTED() {
    Blynk.syncVirtual(V1);  // will cause BLYNK_WRITE(V1) to be executed
}

void loop() {
    Blynk.run();
    timer.run();
}