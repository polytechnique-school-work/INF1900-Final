/*
 * Utilité : Fichier de base du projet
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
#define F_CPU 8000000UL

#include <Can/Can.hpp>
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
    DDRA &= ~(1 << PORTA2);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {
    init();
    // Translator translator = Translator();
    // translator.translate(wheels, light);
    // return 0;
    while (true) {
        Can can;
        uint8_t value = uint8_t(can.lecture(2) >> 2);
        DEBUG_PRINT((1200/(value-20))); // 600 = 80cm
                                        // 10 = 10cm
                                        // 15 = 15cm
                                        // 1 d'espacement = 35/40.
        _delay_ms(50);
    }

    return 0;
}