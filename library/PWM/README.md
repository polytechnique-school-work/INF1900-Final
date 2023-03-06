<h1>Gestion de la PWM</h1>

Ce module est plutôt simple, il permet de gérer facilement la PWM à l'aide d'une valeur qui doit être située entre 0 et 100.

Dans la grande majorité des cas, ce module ne sera pas directement utilisé.
En effet, il sera majoritairement utilisé par le système de roue (WheelManager).

⚠️ Très important, ne pas oublier de mettre la lumière en DDRD = 0xFF si une lumière est utilisée.
<hr>

## Différentes méthodes

`editValue()` : Permet de changer une seule valeur de PWM.

`editValues()` : Permet de changer les deux valeurs de PWM.

<h2>Exemple d'utilisation</h2>

```c++
#include <Pwm/Pwm.hpp>

int main() {
    Pwm pwm;
    
    // Premier cas d'utilisation où on modifie
    // les deux valeurs.
    pwm.editValues(10, 20);
    
    // Deuxième cas d'utilisation où on modifie
    // une seule valeur.
    pwm.editValue(PwmValues::FIRST, 10);
}
```