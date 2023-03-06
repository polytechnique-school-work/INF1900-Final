<h1>Gestion des roues</h1>

Système de gestion des roues. Il permet de faire avancer les roues, de les faire reculer, de faire en sorte que le robot se dirige vers la droite ou vers la gauche.
<hr>

## Différentes méthodes

`setDirection()` : Permet de changer la direction (RIGHT, LEFT, FORWARD, BACKWARD).

`setSpeed()` : Permet de changer la vitesse, obligatoirement entre 0 et 100.

`update()` : Permet de sauvegarder les informations dans les registres.

<h2>Exemple d'utilisation</h2>

```cpp
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
```