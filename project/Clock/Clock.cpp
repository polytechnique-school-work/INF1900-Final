#include "Clock.hpp"

volatile uint32_t timestamp = 0;

static const uint16_t TIMER_TICKS = 312;

void Clock::init() {
    sei(); // Accepter de recevoir des intéruptions
    // mode CTC du timer 0 avec horloge divisée par 256
    // interruption après la durée spécifiée
    TCNT1  = 0;           // Ici on met le début du compteur.
    OCR1A  = TIMER_TICKS; // Équivaut à 0.00816s à chaque fois > 0.009984s
    TCCR1A = (1 << WGM12);
    TCCR1B = (1 << CS12); // /256
    TIMSK1 = (1 << OCIE1A);
}

volatile uint32_t Clock::getTimestamp() { return timestamp * 1.001602564; }

ISR(TIMER1_COMPA_vect) {
    timestamp += 1;
    TCNT1 = 0; // Reset du compteur
}