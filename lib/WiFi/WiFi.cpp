#include "wifi.h"

#include <ESP8266WiFi.h>

#include "constant.h"

IPAddress setupWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }

    IPAddress ipAdress = WiFi.localIP();
    Serial.println(ipAdress);

    return ipAdress;
}