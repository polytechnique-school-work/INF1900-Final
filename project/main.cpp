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

LightManager light                  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
Memoire24CXXX memory                = Memoire24CXXX();
static const uint16_t STARTUP_DELAY = 2000;

void init() {
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {
    Clock clock;
    clock.init();

    uint8_t abc[5] = "ABC";
    memory.ecriture(0, abc, 3);

    Emetteur emetteur = Emetteur(light, memory, clock);
    emetteur.ExecuteRoutine();
    
}