#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
class TimerManager {
public:
    static void runTimer(uint16_t duration);
    static bool isDone();
};