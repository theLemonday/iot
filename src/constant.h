#ifndef CONSTANT_H
#define CONSTANT_H

const int BAUD_RATE = 115200;
// const char SSID[] = "Iot-Wifi";
// const char WIFI_PASSWORD[] = "11593195";

const char SSID[] = "Phòng máy 401";
const char WIFI_PASSWORD[] = "UET@#VNU";
const char HOST_IP[] = "192.168.0.101";
const uint16_t HOST_PORT = 8080;

void setupBaudRate() {
    Serial.begin(BAUD_RATE);
}

#endif