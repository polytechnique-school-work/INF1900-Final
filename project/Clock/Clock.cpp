#include "Clock.hpp"

volatile uint32_t timestamp = 0;

static const uint8_t TIMER_TICKS = 255;

void Clock::init() {
    sei(); // Accepter de recevoir des intéruptions
    // mode CTC du timer 0 avec horloge divisée par 256
    // interruption après la durée spécifiée
    TCNT0 = 0; // Ici on met le début du compteur.
    OCR0A = TIMER_TICKS; // Équivaut à 0.00816s à chaque fois
    TCCR0A = (1 << WGM02);
    TCCR0B = (1 << CS02); // /256
    TIMSK0 = (1 << OCIE0A);
}

volatile uint32_t Clock::getTimestamp() { return timestamp; }


ISR(TIMER0_COMPA_vect) { 
    timestamp += 1;
    TCNT0 = 0; // Reset du compteur
}