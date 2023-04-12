#include "Sensor.hpp"
#include "Logger/Logger.hpp"
#include "math.h"

uint16_t Sensor::readValue() {
    uint8_t value = uint8_t(this->can.lecture(2) >> 2);
    return 1317.6 * powf(value, -0.874); // 20.094 * powf(value, -0.91); // 316.72 * powf(value,
                                         // -0.545); //(1200 / (value - 20));
}