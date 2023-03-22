#pragma once
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

class SoundPlayer {
private:
public:
    void init();
    void playSound(uint8_t note);
    void reset();
};