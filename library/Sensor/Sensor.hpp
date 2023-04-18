#pragma once
#include "Can/Can.hpp"
#include <avr/io.h>
#include <stdio.h>

class Sensor {
public:
    // Sensor();
    uint16_t readValue();

private:
    Can can = Can();
};