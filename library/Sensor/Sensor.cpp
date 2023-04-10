#include "Sensor.hpp"
#include "Logger/Logger.hpp"

uint16_t Sensor::readValue() {
    DEBUG_PRINT("Hello");
    uint8_t value = uint8_t(this->can.lecture(2) >> 2);
    return (1200 / (value - 20));
}