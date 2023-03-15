#pragma once
#include <avr/io.h>

// Utilise le timer 0 afin de pouvoir utiliser la PWM des roues ET une minuterie en même temps.

enum class Note { DO = 5, RE = 10 };

class SoundPlayer {
private:
public:
    void init();
    void playSound(Note note, int activeTime, int period);
    void reset();
};