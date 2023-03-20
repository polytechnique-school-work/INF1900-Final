#include "SoundPlayer.hpp"
#include <Logger/Logger.hpp>

static int notes[37] = {4545, 4290, 4050, 3822, 3608, 3405, 3214, 3034, 2863, 2703,
                        2551, 2408, 2273, 2145, 2025, 1911, 1804, 1703, 1607, 1517,
                        1432, 1351, 1276, 1204, 1136, 1073, 1012, 956,  902,  851,
                        804,  758,  716,  676,  638,  602,  568};

void SoundPlayer::init() { DDRB |= (1 << PORTB2) | (1 << PORTB3); }

void SoundPlayer::reset() {
    TCCR0A &= ~(1 << COM0A0); // set à 0
}

void SoundPlayer::playSound(uint8_t note) {
    reset();
    //if(note > 82) return;
    OCR0A = notes[note - 45] /*Fréquence calculée*/;
    // OCR2B; J'imagine qu'on en a pas besoin, on souhaite juste faire une seule fréquence, on
    // a pas 2 instruments en même temps non?
    TCCR0A = (1 << COM0A0);
    TCCR0B = (1 << WGM02) | (1 << CS01); //| (1 << CS00);
}

void loop(uint16_t duration) {
    for (uint16_t i = 0; i < duration; i++) {
        _delay_ms(1);
    }
}

// void SoundPlayer::playSound(uint8_t note, uint8_t duration) {
//     this->playSound(note);
//     loop(duration);
// }

void SoundPlayer::playSound(uint8_t note, uint16_t duration, uint16_t delayAfter) {
    this->playSound(note);
    loop(duration);
    reset();
    loop(delayAfter);
}