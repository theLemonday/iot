#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Sensor.h>
#include <WebSocketsClient.h>

#include "constant.h"
#include "wifi.h"

WebSocketsClient webSocket;

Sensor MQ2Sensor(A0, D0);

const int MOISTURE_REPONSE_CAPACITY = JSON_OBJECT_SIZE(3);

const unsigned long INTERVAL = 1000;

unsigned long previousMillis = 0;

bool connected = false;

StaticJsonDocument<70> doc;

String readMQ2Sensor() {
    int value = 0;
    for (int i = 0; i != 10; i++) {
        value += MQ2Sensor.read();
    }
    const int realValue = value / 10;

    StaticJsonDocument<MOISTURE_REPONSE_CAPACITY> data;
    data["type"] = "mq2";
    data["value"] = realValue;
    data["exceed"] = MQ2Sensor.isAboveThreshold();

    String reponse;
    serializeJson(data, reponse);

    return reponse;
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            if (!connected) Serial.printf("[WSc] Disconnected!\n");
            connected = false;
            break;
        case WStype_CONNECTED:
            Serial.printf("[WSc] Connected to url: %s\n", payload);
            break;
        case WStype_TEXT:
            Serial.printf("[WSc] get text: %s\n", payload);
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary length: %u\n", length);
            break;
    }
}

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("ESP8266 Websocket Client");

    WiFi.begin(SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    webSocket.begin(HOST_IP, HOST_PORT);
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();

    const unsigned long currentMillis = millis();
    if ((currentMillis - previousMillis) > INTERVAL) {
        String reponse = readMQ2Sensor();
        webSocket.sendTXT(reponse);

        previousMillis = millis();
    }
}