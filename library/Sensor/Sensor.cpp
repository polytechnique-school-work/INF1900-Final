#include "Sensor.hpp"
#include "Logger/Logger.hpp"
#include "math.h"

// 220 premier
// 250 deuxième
// 150 distance normale

uint16_t Sensor::readValue() {
    uint8_t count    = 5;
    uint16_t somme   = 0;
    uint8_t minValue = 255;

    for (uint8_t i = 0; i < count; i++) {
        uint8_t val = 255 - uint8_t(this->can.lecture(2) >> 2);
        if (val > 250 && val <= 255) val = 255;
        if (val < minValue) {
            minValue = val;
        }
        somme += val;
    }
    somme -= minValue;
    return floor(somme / (count - 1));
}