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
#include "Sensor/Sensor.hpp"
#include "robot/Robot.hpp"
#include <Can/Can.hpp>
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <Wheel/WheelManager.hpp>
#include <util/delay.h>

LightManager light                  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
WheelManager wheels                 = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
static const uint16_t STARTUP_DELAY = 2000;
const uint8_t SPEED                 = 50;

void init() {
    _delay_ms(STARTUP_DELAY);
    DDRA &= ~(1 << PORTA2);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {

    init();
    // Initialisation du robot, donc les roues, etc.

    LightManager light  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
    WheelManager wheels = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
    Sensor sensor       = Sensor();

    Robot robot = Robot(wheels, light, sensor);

    // while (true) {
    //     DEBUG_PRINT(robot.getClock().getTimestamp());
    // }

    // init();

    // uint32_t timestamp = 0;
    // uint16_t lowestValue = 65535;
    // uint32_t FULL_CIRCLE = 500;

    // uint32_t initialTimestamp = clock.getTimestamp();

    // wheels.setDirection(Direction::RIGHT);
    // wheels.setSpeed(SPEED);
    // wheels.update();

    // DEBUG_PRINT(("Test"));

    // Sensor sensor;

    // /*
    //     Vérification pour faire le 360 degrés
    // */

    // while (true) {
    //     uint16_t value = sensor.readValue();
    //     uint32_t nowTimestamp = clock.getTimestamp();
    //     if(value < lowestValue) {
    //         lowestValue = value;
    //         timestamp = nowTimestamp;
    //     }

    //     if(initialTimestamp + FULL_CIRCLE < nowTimestamp) {
    //         DEBUG_PRINT(("STOPED"));
    //         break;
    //     }
    // }

    // wheels.setSpeed(0);
    // wheels.update();

    // uint32_t deplacementNeeded = timestamp - initialTimestamp;

    // _delay_ms(500);

    // /*
    //     Tourner pour voir le bloc
    // */

    // uint32_t turnTime = clock.getTimestamp();

    // wheels.setSpeed(SPEED);
    // wheels.setDirection(Direction::LEFT);
    // wheels.update();

    // while(true) {
    //     if(clock.getTimestamp() > turnTime + deplacementNeeded) break;
    // }

    // wheels.setSpeed(0);
    // wheels.update();
    // _delay_ms(500);

    // wheels.setSpeed(SPEED);
    // wheels.setDirection(Direction::FORWARD);
    // wheels.update();

    // while(true) {
    //     if(sensor.readValue() < 15) break;
    // }

    // wheels.setSpeed(0);
    // wheels.update();

    // return 0;
}