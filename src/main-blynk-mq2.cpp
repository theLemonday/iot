#include <Arduino.h>
#include <Constant.h>
#include <BlynkSimpleEsp8266.h>
#include <Sensor.h>
#include <Relay.h>

BlynkTimer timer;
Sensor MQ2(A0, D0);

void smokeExceedEvent(int value) {
    Blynk.logEvent("smoke_detected", String("Current smoke value: ") + String(value));
}

void myTimer() {
    if (MQ2.isAboveThreshold()) {
        smokeExceedEvent(MQ2.read());
        Blynk.virtualWrite(V0, HIGH);
    } else {
        Blynk.virtualWrite(V0, LOW);
    }
}

void setup() {
    Serial.begin(BAUD_RATE);

    timer.setInterval(5000L, myTimer);
    Blynk.begin(BLYNK_AUTH_TOKEN, SSID, WIFI_PASSWORD);
}

void loop() {
    timer.run();
    Blynk.run();
}