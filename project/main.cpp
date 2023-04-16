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
    _delay_ms(5000);

    Emetteur emetteur = Emetteur();

    emetteur.ExecuteRoutine();   
}