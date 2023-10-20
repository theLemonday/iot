#if !defined(RELAY_H)
#define RELAY_H
#include <Arduino.h>

class Relay {
   private:
    const uint8_t _pin;

   public:
    Relay(const uint8_t pin);

    void on();
    void off();
};

#endif  // RELAY_H
