
#include "TimerManager.hpp"

volatile bool isTimerDone = false;

void TimerManager::runTimer(uint16_t duration) {
    sei(); // Accepter de recevoir des intéruptions
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0; // Ici on met le début du compteur.
    OCR1A = duration * 781.25; // En gros ici on met le nombre maximum à atteindre
    TCCR1A = 0;
    TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12); // Explication page 629 de la documentation, mais en gros ça met le bit 2 et le bit 0 à 1, pour avoir le tout /1024 (normalement).
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
    isTimerDone = false;
}

bool TimerManager::isDone(){
    return isTimerDone;
}

ISR(TIMER1_COMPA_vect) {
    isTimerDone = true;
}