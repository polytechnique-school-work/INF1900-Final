<h1>Gestion de la PWM</h1>
<hr>

Ce module est plutôt simple, il permet de gérer facilement la PWM à l'aide d'une valeur qui doit être située entre 0 et 100.

Dans la grande majorité des cas, ce module ne sera pas directement utilisé.
En effet, il sera majoritairement utilisé par le système de roue (WheelManager).
<hr>
<h2>Exemple d'utilisation</h2>

```c++
#include "Pwm.hpp"

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