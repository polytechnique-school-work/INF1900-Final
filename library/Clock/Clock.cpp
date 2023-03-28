#include "Clock.hpp"
#include "Logger/Logger.hpp"

volatile uint32_t timestamp = 0;

static const uint16_t TIMER_TICKS = 312;

void Clock::init() {
    /*
        À chaque 0.009984s, on incrémente notre timestamp de 1. Ainsi,
        lorsqu'il est vérifié, il doit être multiplié par 1.001602564
        pour récupérer du temps en seconde.

        Mode CTC du timer 1 avec une horloge divisée par 256
    */
    sei();
    TCNT1 = 0;
    // 0,009984 secondes
    OCR1A  = TIMER_TICKS;
    TCCR1A = (1 << WGM12);
    // Division par 256
    TCCR1B = (1 << CS12);
    TIMSK1 = (1 << OCIE1A);

    DEBUG_PRINT(("Lancement de la clock."));
}

// Retourne des environs secondes.
uint32_t Clock::getTimestamp() { return timestamp * 1.0016; } // 1.001602564

ISR(TIMER1_COMPA_vect) {
    timestamp += 1;
    TCNT1 = 0; // Reset du compteur
}