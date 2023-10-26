#if !defined(SENSOR_H)
#define SENSOR_H

#include <Arduino.h>

#include <memory>

class Sensor {
   protected:
    const uint8_t _analogPin;
    const uint8_t* _digitalPin;
    const uint8_t* _powerPin;

    Sensor(
        const uint8_t _analogPin,
        const uint8_t* _digitalPin,
        const uint8_t* _powerPin);

   public:
    Sensor(const uint8_t analogPin);
    Sensor(const uint8_t analogPin, const uint8_t& digitalPin);
    Sensor(const uint8_t analogPin, const uint8_t& digitalPin, const uint8_t& powerPin);

    void on();
    void off();
    int read();
    bool isAboveThreshold();
};

class MoistureSensor : public Sensor {
   private:
    int valueToMoisturePercent(int value);

   public:
    MoistureSensor(const uint8_t analogPin);
    MoistureSensor(const uint8_t analogPin, const uint8_t& digitalPin);
    MoistureSensor(const uint8_t analogPin, const uint8_t& digitalPin, const uint8_t& powerPin);
    int readMoisturePercentage();
};

#endif  // SENSOR_H
