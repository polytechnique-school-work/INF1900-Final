<h1>Gestion des roues</h1>

Système de gestion des roues. Il permet de faire avancer les roues, de les faire reculer, de faire en sorte que le robot
se dirige vers la droite ou vers la gauche.
<hr>

<h2>Exemple d'utilisation</h2>

```cpp
#include "WheelManager.hpp"

int main() {
    
    // WheelManager ne devrait être initialisé qu'une
    // seule fois.
    WheelManager wheelManager;
    wheelManager.setSpeed(55); //👈️ Entre 0 et 100
    wheelManager.setDirection(Direction::LEFT);
    
    // Il est important d'update, puisque ça permet
    // à la modification d'être active pour le robot.
    wheelManager.update();
}
```