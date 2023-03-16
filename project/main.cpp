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
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>

static const uint16_t STARTUP_DELAY = 2000;

WheelManager wheels = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
LightManager light  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
Color color         = Color::OFF;

void init() {
    _delay_ms(STARTUP_DELAY);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {
    init();
    Translator translator;
    translator.translate(wheels, light, color);
    // DDRB = 0xff;
    SoundPlayer soundPlayer;
    soundPlayer.init();
    uint16_t noire         = 750;
    uint16_t croche        = 187;
    uint16_t noirePointe   = 281;
    uint16_t double_croche = 94;

    soundPlayer.playSound(62, noirePointe);
    soundPlayer.playSound(65, noirePointe);
    soundPlayer.playSound(62, noirePointe, 110);
    soundPlayer.playSound(62, double_croche);
    soundPlayer.playSound(67, croche);
    soundPlayer.playSound(62, croche);
    soundPlayer.playSound(60, croche);

    soundPlayer.playSound(62, noirePointe);
    soundPlayer.playSound(69, noirePointe);
    soundPlayer.playSound(62, noirePointe, 110);
    soundPlayer.playSound(62, double_croche);
    soundPlayer.playSound(70, croche);
    soundPlayer.playSound(69, croche);
    soundPlayer.playSound(65, croche);

    soundPlayer.playSound(62, croche);
    soundPlayer.playSound(69, croche);
    soundPlayer.playSound(74, croche);
    soundPlayer.playSound(62, croche);
    soundPlayer.playSound(60, noirePointe, 110);
    soundPlayer.playSound(60, double_croche);
    soundPlayer.playSound(57, noirePointe);
    soundPlayer.playSound(64, double_croche);
    soundPlayer.playSound(62, noire, 120);

    soundPlayer.playSound(62, noirePointe);
    soundPlayer.playSound(62, noirePointe);
    soundPlayer.reset();
}