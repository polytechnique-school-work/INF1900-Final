/*
 * Utilité : Fichier de base du projet
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
#define F_CPU 8000000UL
// #include <util/delay.h>
// #include "SoundPlayer/SoundPlayer.hpp"
#include "Translator/Translator.hpp"
// #include <Light/LightManager.hpp>
// #include <Logger/Logger.hpp>

#include <Light/LightManager.hpp>
#include <util/delay.h>
#include <Memory/memoire_24.h>
#include <Logger/Logger.hpp>
#include <Wheel/WheelManager.hpp>

WheelManager wheels = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
LightManager light  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
static const uint16_t STARTUP_DELAY = 2000;


void init() {
    _delay_ms(STARTUP_DELAY);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}


int main() {

    init();

    Translator translator = Translator();
    translator.translate(wheels, light);
    return 0;
}