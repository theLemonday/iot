#if !defined(LED_H)
#define LED_H
#include <Arduino.h>

class LED {
   private:
    const uint8_t _pin;

   public:
    enum State {
        ON,
        OFF
    };

    LED(uint8_t pin);

    void setup();
    void on();
    void off();
    State getCurrentState();
};

#endif  // LED_H