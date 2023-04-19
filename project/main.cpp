
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
#include "Transmission/transmission.hpp"
#include "robot/Robot.hpp"
#include "structure/Executer.hpp"
#include <Can/Can.hpp>
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <util/delay.h>

#include "Constantes.hpp"
#include "FetchRoutine.hpp"

void init() {
    _delay_ms(STARTUP_DELAY);
    // Pourquoi est-ce qu'on met un set ici? Il sert vraiment à quelque chose?
    DDRA &= ~(1 << PORTA2);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {

    _delay_ms(5000);

     Memoire24CXXX memory = Memoire24CXXX();

    uint8_t coordonnees[16] = {2, 2, 3, 3, 5, 3, 7, 1, 6, 0, 2, 0, 255, 255, 255, 255};
    memory.ecriture(0, coordonnees, 16);

    _delay_ms(1000);

    Emetteur emetteur = Emetteur();

    emetteur.ExecuteRoutine();

    // init();

    // // Initialisation du robot, donc les roues, etc.
    // LightManager light  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
    // WheelManager wheels = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
    // SoundPlayer sound   = SoundPlayer();
    // Sensor sensor       = Sensor();
    // sound.init();
    // Clock::init();

    // Robot robot = Robot(&wheels, &light, &sensor, &sound);

   

    // while (true) {
    //     Logger::log(Priority::INFO, sensor.readValue());
    //     _delay_ms(50);
    // }

    // Executer execute = Executer();
    // execute.executeRoutine(robot);

    // // FetchRoutine fetchRoutine = FetchRoutine();
    // // Direction direction       = Direction::RIGHT;

    // // fetchRoutine.fetchBlock(robot, 1);

    // // fetchRoutine.recalibrateDirection(robot, 223, direction);

    // // MagicalWheels magicWheels = MagicalWheels(robot);
    // // DEBUG_PRINT((magicWheels.changeHeadDirection(0, Direction::LEFT)));

    // // magicWheels.stopMoves();
}