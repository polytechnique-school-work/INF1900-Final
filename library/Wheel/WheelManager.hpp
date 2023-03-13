/*
 * Utilité : Ce module permet de gérer les roues.
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie: PORTD6, PORTD7 et deux autres ports au choix.
 * */
#pragma once
#include <avr/io.h> 
enum class Direction {
    FORWARD, BACKWARD, RIGHT, LEFT
};

enum class Wheel {
    RIGHT, LEFT
};

class WheelManager {
private:
    volatile uint8_t* registre;
    volatile uint8_t* port;
    uint8_t pinLeft;
    uint8_t pinRight;
    uint8_t speed;
    Direction direction;
    void setWheel(Wheel wheel, Direction direction);
public:
    // Exemple : WheelManager(&DDRD, &PORTD, PORTD6, PORTD7);
    WheelManager(volatile uint8_t* registre, volatile uint8_t* port, uint8_t pinLeft, uint8_t pinRight);
    WheelManager setDirection(Direction direction);
    WheelManager setSpeed(uint8_t speed);
    void update();
};