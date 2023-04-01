#include "SoundPlayer.hpp"
#include "Logger/Logger.hpp"

// static int notes[37] = {4545, 4290, 4050, 3822, 3608, 3405, 3214, 3034, 2863, 2703,
//                         2551, 2408, 2273, 2145, 2025, 1911, 1804, 1703, 1607, 1517,
//                         1432, 1351, 1276, 1204, 1136, 1073, 1012, 956,  902,  851,
//                         804,  758,  716,  676,  638,  602,  568};

// void SoundPlayer::init() { DDRD |= (1 << PORTD4) | (1 << PORTD5); }

// void SoundPlayer::reset() {
//     TCCR1A &= ~(1 << COM1A0);
// }

// void SoundPlayer::playSound(uint8_t note) {
//     reset();
//     if(note > 82) return;
//     OCR1A = notes[note - 45];
//     TCCR1A = (1 << COM1A0);
//     TCCR1B = (1 << WGM12) | (1 << CS11);
// }

// void loop(uint16_t duration) {
//     for (uint16_t i = 0; i < duration; i++) {
//         _delay_ms(1);
//     }
// }

void SoundPlayer::init() { DDRB |= (1 << PORTB2) | (1 << PORTB3); }

void SoundPlayer::reset() {
    TCCR0A &= ~(1 << COM0A0);
}

// En gros, jsp comment changer OCR0A pour faire changer la note de la musique
// Mais, j'ai appris que le prescaler impact la note donc voici une solution inhabituel

void SoundPlayer::playSound(uint8_t note) {
    reset();

    if (note == 1) { // note est grave
    TCCR0A = (1 << COM0A0);
    TCCR0B = (1 << WGM02) | (1 << CS02);
    }
    else if (note == 2) { // note est aigu
    TCCR0A = (1 << COM0A0);
    TCCR0B = (1 << WGM02) | (1 << CS00) | (1 << CS01);
    }
}


/*

vitesse = 8 000 000 / prescaler
frequence = 1/T
temps actif = 1/2T

*/