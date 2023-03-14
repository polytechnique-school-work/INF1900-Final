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

    soundPlayer.playSound(62,noire);
    soundPlayer.playSound(65,noire);
    soundPlayer.playSound(62,noirePointe);
    soundPlayer.playSound(62,double_croche);
    soundPlayer.playSound(67,noire);
    soundPlayer.playSound(62,croche);
    soundPlayer.playSound(60,croche);

    soundPlayer.playSound(62,noire);
    soundPlayer.playSound(69,noire);
    soundPlayer.playSound(62,noirePointe);
    soundPlayer.playSound(62,double_croche);
    soundPlayer.playSound(70,noire);
    soundPlayer.playSound(69,croche);
    soundPlayer.playSound(65,croche);

    soundPlayer.playSound(62,croche);
    soundPlayer.playSound(69,croche);
    soundPlayer.playSound(74,croche);
    soundPlayer.playSound(64,croche);
    soundPlayer.playSound(60,noirePointe);
    soundPlayer.playSound(60,double_croche);
    soundPlayer.playSound(57,croche);
    soundPlayer.playSound(64,croche);
    soundPlayer.playSound(62,noire);

}