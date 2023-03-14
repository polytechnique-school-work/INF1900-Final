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
    // DDRB = 0xff;
    SoundPlayer soundPlayer;
    soundPlayer.init();
    uint16_t noire         = 500;
    uint16_t croche        = 250;
    uint16_t noirePointe   = 375;
    uint16_t double_croche = 125;

    soundPlayer.playSound(1703,noire);
    soundPlayer.playSound(1432,noire);
    soundPlayer.playSound(1703,noirePointe);
    soundPlayer.playSound(1703,double_croche);
    soundPlayer.playSound(1276,noire);
    soundPlayer.playSound(1703,croche);
    soundPlayer.playSound(1911,croche);

    soundPlayer.playSound(1703,noire);
    soundPlayer.playSound(1136,noire);
    soundPlayer.playSound(1703,noirePointe);
    soundPlayer.playSound(1703,double_croche);
    soundPlayer.playSound(1073,noire);
    soundPlayer.playSound(1136,croche);
    soundPlayer.playSound(1432,croche);

    soundPlayer.playSound(1703,croche);
    soundPlayer.playSound(1136,croche);
    soundPlayer.playSound(851,croche);
    soundPlayer.playSound(1517,croche);
    soundPlayer.playSound(1911,noirePointe);
    soundPlayer.playSound(1911,double_croche);
    soundPlayer.playSound(2273,croche);
    soundPlayer.playSound(1517,croche);
    soundPlayer.playSound(1703,noire);

}