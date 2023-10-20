#include "Relay.h"

Relay::Relay(const uint8_t pin) : _pin(pin) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Relay::on() {
    digitalWrite(_pin, HIGH);
}
void Relay::off() {
    digitalWrite(_pin, LOW);
}