#pragma once
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
/*
    La valeur maximale d'un uint16_t est de 65 536.
    Si on considère que l'épreuve devrait durée environ 10 minutes.
    On pourrait donc avoir 10 * 60 * 100, donc une précision de 0.01s => 0.009984s = une incrémentation.
    On atteindrait donc un maximum de 10,92 minutes.

    On va se prévoir une PWM spéciale pour le clock.
    Le but est de pouvoir obtenir un "timestamp" relatif au lancement du robot.
*/

class Clock {
    public:
        static void init();
        static uint16_t getTimestamp();
};