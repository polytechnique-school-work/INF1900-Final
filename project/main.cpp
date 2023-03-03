#include <avr/io.h>
#include <Wheel/WheelManager.hpp>

int main() {
    // Déterminer les ports utilisés par les roues.
    // Les ports de PWM sont obligés d'être PORTD5 et PORTD6.
    WheelManager wheels(&DDRD, &PORTD, PORTD6, PORTD7);

    wheels.setDirection(Direction::RIGHT);
    wheels.setSpeed(100); //👈️ Entre 0 et 100

    // Update très important, il permet de sauvegarder les
    // informations et de les envoyer vers le robot.
    // 🔍️ Il fait l'écriture dans les registres.
    wheels.update();
}