#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Selon les types définis à la page 68 de la documentation.
enum class InterruptType {ANY, FALLING_EDGE, RISING_EDGE};
enum class ClickType {CLICK, UNCLICK, NONE};
class ExternInterrupt {
public:
    static void init(InterruptType interruptType);
    static volatile uint8_t getInterruptCount();
    static void resetInterruptCount();
    static ClickType getLastClickType();
    static const char* convertClickTypeToString(ClickType clickType);
};