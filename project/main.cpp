/*
 * Utilité : Fichier de base du projet
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
#define F_CPU 8000000UL

#include "Clock/Clock.hpp"
#include "Transmission/transmission.hpp"
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <util/delay.h>


static const uint16_t STARTUP_DELAY = 2000;

int main() {
    _delay_ms(2000);
    LightManager light = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
    Memoire24CXXX memory = Memoire24CXXX();
    uint8_t indices[6] = {8, 9, 26, 30, 16, 13};
    SVG svg = SVG(memory);

    for(uint8_t i : indices){
        svg.visiterPoint(i);
    }

    _delay_ms(500);
    Logger::log(Priority::INFO, "Le programme est lancé.");
    Clock clock;
    clock.init();
    Emetteur emetteur = Emetteur(light, memory, clock, svg);
    svg.ecrireSVGMemoire();

    emetteur.ExecuteRoutine();   
}