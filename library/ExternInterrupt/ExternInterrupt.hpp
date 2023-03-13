/*
 * Utilité : Ce module permet de détecter des interruptions externes.
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée: PORTD2
 *  Sortie:
 * */
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