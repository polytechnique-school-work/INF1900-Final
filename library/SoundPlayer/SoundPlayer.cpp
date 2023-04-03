#include "SoundPlayer.hpp"
#include "Logger/Logger.hpp"

static uint8_t notes[26] = {141, 133, 125, 118, 111, 105, 99, 93, 88, 83, 78, 74, 70,
                            66,  62,  58,  55,  52,  49,  46, 43, 41, 38, 36, 34, 32,
                            30,  28,  27,  25,  24,  22,  21, 20, 18, 17, 16};

void SoundPlayer::init() { DDRB |= (1 << PORTB2) | (1 << PORTB3); }

void SoundPlayer::reset() { TCCR0A &= ~(1 << COM0A0); }

// En gros, jsp comment changer OCR0A pour faire changer la note de la musique
// Mais, j'ai appris que le prescaler impact la note donc voici une solution inhabituel

void SoundPlayer::playSound(uint8_t note) {
    reset();
    OCR0A  = notes[note - 45]; // note est grave
    TCCR0A = (1 << WGM01) | (1 << COM0A0);
    TCCR0B = (1 << CS02);
}
