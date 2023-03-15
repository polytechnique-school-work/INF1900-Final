/*
 * Utilité : Fichier de base du projet
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
#define F_CPU 8000000UL
#include "SoundPlayer/SoundPlayer.hpp"
#include "Translator/Translator.hpp"
#include <Logger/Logger.hpp>
#include <util/delay.h>

static const uint16_t STARTUP_DELAY = 2000;

void init() {
    _delay_ms(STARTUP_DELAY);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {
    init();
    // Translator translator;
    // translator.translate();
    SoundPlayer soundPlayer;
    soundPlayer.init();
    soundPlayer.playSound(Note::DO, 5, 5);
    _delay_ms(10000);
    soundPlayer.reset();
}