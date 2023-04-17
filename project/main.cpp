
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
#include "Routine/detection.hpp"
#include "Sensor/Sensor.hpp"
#include "robot/Robot.hpp"
#include "structure/Executer.hpp"
#include <Can/Can.hpp>
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <Wheel/WheelManager.hpp>
#include <util/delay.h>

#include "FetchRoutine.hpp"

static const uint16_t STARTUP_DELAY = 2000;

void init() {
    _delay_ms(STARTUP_DELAY);
    // Pourquoi est-ce qu'on met un set ici? Il sert vraiment à quelque chose?
    DDRA &= ~(1 << PORTA2);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {

    init();

    // Initialisation du robot, donc les roues, etc.
    LightManager light  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
    WheelManager wheels = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
    SoundPlayer sound   = SoundPlayer();
    Sensor sensor       = Sensor();
    sound.init();

    Robot robot = Robot(&wheels, &light, &sensor, &sound);

    // while (true) {
    //     DEBUG_PRINT((sensor.readValue()));
    //     _delay_ms(50);
    // }

    Executer execute = Executer();
    execute.executeRoutine(robot);
}