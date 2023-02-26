#pragma once
#include <avr/io.h> 

enum class Color { RED, GREEN, AMBER, OFF };

class LightManager {
private:
    static const uint8_t DelayGREEN = 15;
    static const uint8_t DelayRED = 5;
    volatile uint8_t* regis;
    volatile uint8_t* port;
    uint8_t firstPin;
    uint8_t secondPin;

public:
    LightManager(volatile uint8_t* registre, volatile uint8_t* port, uint8_t pinFirst, uint8_t pinSecond);
    void setLight(Color color);
};