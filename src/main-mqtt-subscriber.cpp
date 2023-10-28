#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Constant.h>
#include <LED.h>
#include <Sensor.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define MQTT_SENSING_DATA_TITLE "sensingDataTeam6"
#define MQTT_LED_STATUS_TITLE "sensingDataTeam6"

// Update these with values suitable for your network.

const char mqtt_server[] = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.subscribe(MQTT_SENSING_DATA_TITLE);
            client.subscribe(MQTT_LED_STATUS_TITLE);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void callback(char* topic, uint8_t* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setup() {
    setupBaudRate();
    setupWifi();

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
