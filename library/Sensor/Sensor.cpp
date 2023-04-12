#include "Sensor.hpp"
#include "Logger/Logger.hpp"
#include "math.h"

uint16_t Sensor::readValue() {
    uint8_t value = uint8_t(this->can.lecture(2) >> 2);
    uint16_t val  = 1317.6 * powf(value, -0.874);
    if (val < 10) return 65535;
    return val;
}