/*
 * Utilité : Ce module permet de gérer une minuterie.
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
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