#include "SoundPlayer.hpp"

static int notes[37] = {4545, 4290, 4050, 3822, 3608, 3405, 3214, 3034, 2863, 2703,
                        2551, 2408, 2273, 2145, 2025, 1911, 1804, 1703, 1607, 1517,
                        1432, 1351, 1276, 1204, 1136, 1073, 1012, 956,  902,  851,
                        804,  758,  716,  676,  638,  602,  568};

void SoundPlayer::init() { DDRD |= (1 << PORTD4) | (1 << PORTD5); }

void SoundPlayer::reset() {
    TCCR1A &= ~(1 << COM1A0); // set à 0
}

void SoundPlayer::playSound(uint8_t note) {
    OCR1A = 4545 /*Fréquence calculée*/;
    // OCR2B; J'imagine qu'on en a pas besoin, on souhaite juste faire une seule fréquence, on
    // a pas 2 instruments en même temps non?
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS11); //| (1 << CS00);
}