#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Relay.h>
#include <Sensor.h>
#include <WebSocketsClient.h>

#include "constant.h"
#include "wifi.h"

WebSocketsClient webSocket;

Sensor moistureSensor(A0, D0);
Relay pumpRelay(D2);

const int REPONSE_CAPACITY = JSON_OBJECT_SIZE(3);

const unsigned long INTERVAL = 1000;

unsigned long previousMillis = 0;

bool connected = false;

StaticJsonDocument<70> doc;

int valueToMoisturePercent(int value) {
    int percent = map((long)value, 0, 1023, 0, 100);
    percent = 100 - percent;
    return percent;
}

String readMoistureSensor() {
    int value = 0;
    for (int i = 0; i != 10; i++) {
        value += moistureSensor.read();
    }
    const int realValue = value / 10;

    StaticJsonDocument<REPONSE_CAPACITY> data;
    data["type"] = "moisture";
    data["moisture_percent"] = valueToMoisturePercent(realValue);
    data["exceed"] = moistureSensor.isAboveThreshold();

    String reponse;
    serializeJson(data, reponse);
    Serial.println(valueToMoisturePercent(realValue));

    return reponse;
}

void handleWebSocketMessage(WebSocketsClient &client, const uint8_t *payload) {
    DeserializationError err = deserializeJson(doc, payload);
    if (err) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.f_str());
    }

    auto msgType = doc["type"].as<String>();

    if (msgType != "pump") return;

    auto action = doc["action"].as<String>();
    Serial.println(action);
    if (action == "on") {
        client.sendTXT("Turned on relay");
        pumpRelay.on();
    } else if (action == "off") {
        client.sendTXT("Turned off relay");
        pumpRelay.off();
    }
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
            handleWebSocketMessage(webSocket, payload);
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
        String reponse = readMoistureSensor();
        webSocket.sendTXT(reponse);

        previousMillis = millis();
    }
}