#include "SoundPlayer.hpp"

void SoundPlayer::init() { DDRB |= (1 << PORTB3); }

void SoundPlayer::reset() {
    TCCR0A &= ~(1 << COM0A0); // set à 0
}

void SoundPlayer::playSound(Note note, int activeTime, int period) {
    OCR0A = 568 /*Fréquence calculée*/;
    // OCR2B; J'imagine qu'on en a pas besoin, on souhaite juste faire une seule fréquence, on
    // a pas 2 instruments en même temps non?
    TCCR0A = (1 << COM0A0);
    TCCR0B = (1 << WGM02) | (1 << CS12);
}