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
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// Selon les types définis à la page 68 de la documentation.
enum class InterruptType { ANY, FALLING_EDGE, RISING_EDGE };
enum class Button { FIRST, SECOND };
enum class ClickType { CLICK, UNCLICK, NONE };
class ExternInterrupt {
public:
    static void init(InterruptType interruptType, Button button);
    static volatile uint8_t getInterruptCount(Button button);
    static void resetInterruptCount(Button button);
    static ClickType getLastClickType(Button button);
    static const char* convertClickTypeToString(ClickType clickType);
};