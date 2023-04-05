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
    LightManager light = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
    Memoire24CXXX memory = Memoire24CXXX();
    _delay_ms(500);
    Logger::log(Priority::INFO, "Le programme est lancé.");
    Clock clock;
    clock.init();
    Emetteur emetteur = Emetteur(light, memory, clock);

    uint8_t abc[5] = "ABC";
    memory.ecriture(emetteur.getAdresse(), abc, 3);
    emetteur.ecritureMemoire(3);

    emetteur.ExecuteRoutine();   
}