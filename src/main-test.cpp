#include <Arduino.h>
#define BLYNK_AUTH_TOKEN "DdaP7Xfrkpx46baf33xKq22TWfMYG8Du"
#define BLYNK_TEMPLATE_ID "TMPL6_PtbDBh2"
#define BLYNK_TEMPLATE_NAME "pantheon"

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <LED.h>
#include <Sensor.h>

#include "constant.h"

BlynkTimer timer;

// Sensor MQ2sensor(A0, D0, D1);
LED led(LED_BUILTIN);
int lightSensor;

void myTimer() {
    Blynk.virtualWrite(V2, lightSensor);
}

void setup() {
    Serial.begin(BAUD_RATE);

    timer.setInterval(5000L, myTimer);
    Blynk.begin(BLYNK_AUTH_TOKEN, SSID, WIFI_PASSWORD);
}

BLYNK_WRITE(V0) {
    if (param.asInt() == 1) {
        led.on();
        lightSensor = 1;
    } else {
        led.off();
        lightSensor = 0;
    }
}

void loop() {
    timer.run();
    Blynk.run();
}