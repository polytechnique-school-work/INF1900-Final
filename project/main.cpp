/*
 * Utilité : Fichier de base du projet
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
#define F_CPU 8000000UL

#include "Translator/Translator.hpp"
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <Wheel/WheelManager.hpp>
#include <util/delay.h>

LightManager light                  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
WheelManager wheels                 = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
static const uint16_t STARTUP_DELAY = 2000;

void init() {
    _delay_ms(STARTUP_DELAY);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {
    init();
    Translator translator = Translator();
    translator.translate(wheels, light);

    // wheels.setDirection(Direction::LEFT);
    // wheels.setSpeed(100); // 550 pour 100 et 1100 pour 50
    // wheels.update();
    // _delay_ms(550);
    // wheels.setSpeed(0);
    // wheels.update();
    return 0;
}

// #include <avr/io.h>
// #include <Wheel/WheelManager.hpp>

// int main()
// {
//     // Déterminer les ports utilisés par les roues.
//     // Les ports de PWM sont obligés d'être PORTD5 et PORTD6.

//     WheelManager wheels(&DDRD, &PORTD, PORTD5, PORTD4);

//     wheels.setDirection(Direction::RIGHT);
//     wheels.setSpeed(100); // 👈️ Entre 0 et 100

//     // Update très important, il permet de sauvegarder les
//     // informations et de les envoyer vers le robot.
//     // 🔍️ Il fait l'écriture dans les registres.
//     wheels.update();
// }