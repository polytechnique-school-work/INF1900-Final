#include "Sensor.hpp"

uint16_t Sensor::readValue() {
    uint8_t value = uint8_t(this->can.lecture(2) >> 2);
    return (1200/(value-20));
}