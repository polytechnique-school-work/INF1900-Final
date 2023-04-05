#pragma once
#include "Can/Can.hpp"
#include <avr/io.h>
#include <stdio.h>

class Sensor {
public:
    uint16_t readValue();

private:
    Can can;
};