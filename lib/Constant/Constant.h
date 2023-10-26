#ifndef CONSTANT_H
#define CONSTANT_H
#include <Arduino.h>

const int BAUD_RATE = 115200;
void setupBaudRate() {
    Serial.begin(BAUD_RATE);
}

#define BLYNK_TEMPLATE_ID "TMPL6R2Gccxx7"
#define BLYNK_TEMPLATE_NAME "Two Sensor One Actuator"
#define BLYNK_AUTH_TOKEN "L3ezb9bvYGbRzzpMfnL5U9ewlOYIbep0"

const char SSID[] = "Iot-Wifi";
const char WIFI_PASSWORD[] = "11593195";
// const char SSID[] = "Phòng máy 401";
// const char WIFI_PASSWORD[] = "UET@#VNU";

const char HOST_IP[] = "192.168.0.101";
const uint16_t HOST_PORT = 8080;

#endif