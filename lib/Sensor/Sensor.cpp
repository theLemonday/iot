#include "Sensor.h"

Sensor::Sensor(
    const uint8_t analogPin,
    const uint8_t* digitalPin,
    const uint8_t* powerPin) : _analogPin(analogPin),
                               _digitalPin(digitalPin),
                               _powerPin(powerPin) {
    pinMode(analogPin, INPUT);

    if (_digitalPin != nullptr) {
        pinMode(*_digitalPin, INPUT);
    }

    if (_powerPin != nullptr) {
        pinMode(*_powerPin, OUTPUT);
        off();
    }
}

Sensor::Sensor(const uint8_t analogPin) : Sensor(analogPin, nullptr, nullptr) {}

Sensor::Sensor(const uint8_t analogPin, const uint8_t& digitalPin) : Sensor(analogPin, &digitalPin, nullptr) {}

Sensor::Sensor(const uint8_t analogPin, const uint8_t& digitalPin, const uint8_t& powerPin) : Sensor(analogPin, &digitalPin, &powerPin) {}

void Sensor::on() {
    digitalWrite(*_powerPin, HIGH);
    Serial.println(*_powerPin);
}

void Sensor::off() {
    digitalWrite(*_powerPin, LOW);
    Serial.println(*_powerPin);
}

int Sensor::read() {
    return analogRead(_analogPin);
}

bool Sensor::isAboveThreshold() {
    return digitalRead(*_digitalPin) == HIGH;
}

MoistureSensor::MoistureSensor(const uint8_t analogPin) : Sensor(analogPin) {}
MoistureSensor::MoistureSensor(const uint8_t analogPin, const uint8_t& digitalPin) : Sensor(analogPin, digitalPin) {}
MoistureSensor::MoistureSensor(const uint8_t analogPin, const uint8_t& digitalPin, const uint8_t& powerPin) : Sensor(analogPin, digitalPin, powerPin) {}

int MoistureSensor::valueToMoisturePercent(int value) {
    int percent = map((long)value, 0, 1023, 0, 100);
    percent = 100 - percent;
    return percent;
}

int MoistureSensor::readMoisturePercentage() {
    return valueToMoisturePercent(this->read());
}