#include "Clock.hpp"

volatile uint16_t timestamp = 0;

static const uint8_t TIMER_TICKS = 78;

void Clock::init() {
    sei(); // Accepter de recevoir des intéruptions
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0; // Ici on met le début du compteur.
    OCR1A = TIMER_TICKS; // Équivaut à 0.009984s
    TCCR1A = (1 << WGM12);
    TCCR1B = (1 << CS10) | (1 << CS12); // /1024
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
}

uint16_t Clock::getTimestamp() { return timestamp; }

ISR(TIMER1_COMPA_vect) { 
    timestamp += 1;
    TCNT1 = 0; // Reset du compteur
}