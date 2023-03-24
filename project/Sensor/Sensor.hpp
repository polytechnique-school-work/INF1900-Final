#pragma once
#include <avr/io.h>
#include <stdio.h>
#include <Can/Can.hpp>

class Sensor {
    public:
        uint16_t readValue();
    private:
        Can can;
};