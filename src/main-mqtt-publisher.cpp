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

LED led(D1);
Sensor MQ2(A0);

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long prevMillis = 0;
const unsigned long INTERVAL = 2000L;

const int REPONSE_CAPACITY = JSON_OBJECT_SIZE(2);

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
            client.publish("sensingDataHao", "hello IoT Node...");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup() {
    setupBaudRate();
    setupWifi();

    client.setServer(mqtt_server, 1883);
}

LED::State toggleLED(LED Led) {
    if (Led.getCurrentState() == LED::ON) {
        Led.off();
    } else {
        Led.on();
    }

    return Led.getCurrentState();
}

String readSensor() {
    StaticJsonDocument<REPONSE_CAPACITY> data;
    data["type"] = "smoke";
    data["value"] = MQ2.read();

    String reponse;
    serializeJson(data, reponse);

    return reponse;
}

String convertLEDStatusToJsonReponse(LED::State ledStatus) {
    StaticJsonDocument<REPONSE_CAPACITY> data;
    data["type"] = "led";
    data["status"] = ledStatus == LED::ON ? "on" : "off";

    String reponse;
    serializeJson(data, reponse);
    return reponse;
}

void publishMessage(String title, String msg) {
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(title.c_str(), msg.c_str());
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    unsigned long currentMillis = millis();
    if (currentMillis - prevMillis > INTERVAL) {
        auto ledStatus = toggleLED(led);
        publishMessage(MQTT_LED_STATUS_TITLE, convertLEDStatusToJsonReponse(ledStatus));

        publishMessage(MQTT_SENSING_DATA_TITLE, readSensor());

        prevMillis = currentMillis;
    }
}
