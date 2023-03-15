#pragma once
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

// Utilise le timer 0 afin de pouvoir utiliser la PWM des roues ET une minuterie en même temps.

class SoundPlayer {
private:
public:
    void init();
    void playSound(uint8_t note);
    void playSound(uint8_t note, uint8_t duration);
    void reset();
};