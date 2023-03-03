#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
class TimerManager {
private:
    static bool isAlreadyChecked;
public:
    static void runTimer(uint16_t duration);
    static bool isDone();
    static bool isChecked();
};