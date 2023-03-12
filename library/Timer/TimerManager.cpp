#include "TimerManager.hpp"
#include "Logger/Logger.hpp"

volatile bool isTimerDone = true;
bool TimerManager::isAlreadyChecked = false;

void TimerManager::runTimer(uint16_t duration) {
    static float TENTH_OF_A_SECOND = 781.25;
    if(isTimerDone == false) {
        Logger::init();
        Logger::log(Priority::ERROR, "Un timer a essayé d'être lancé, alors qu'un autre n'est pas terminé.");
        return;
    } 
    sei(); // Accepter de recevoir des intéruptions
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0; // Ici on met le début du compteur.
    OCR1A = duration * TENTH_OF_A_SECOND; // En gros ici on met le nombre maximum à atteindre
    TCCR1A = (1 << WGM12);
    TCCR1B = (1 << CS10) | (1 << CS12); // Explication page 629 de la documentation, mais en gros ça met le bit 2 et le bit 0 à 1, pour avoir le tout /1024 (normalement).
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
    isTimerDone = false;
    isAlreadyChecked = false;
}

bool TimerManager::isDone(){
    return isTimerDone;
}

bool TimerManager::isChecked() {
    if(isTimerDone == true) {
        if(TimerManager::isAlreadyChecked == false) {
            TimerManager::isAlreadyChecked = true;
            return false;
        }
    }
    return isAlreadyChecked;
}

ISR(TIMER1_COMPA_vect) {
    isTimerDone = true;
}