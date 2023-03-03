<h1>Gestion des messages à la console</h1>

Système permettant de logger automatiquement
des informations à la console.

⚠️ Pour que ça fonctionne, le programme serieViaUSB
doit être activé.
Normalement, avec le make debug, il est démarré automatiquement.

<hr>
<h2>Exemple d'utilisation</h2>

```cpp
#define F_CPU 8000000UL
#include <Logger/Logger.hpp>
#include <util/delay.h>

int main() {
    Logger::init();
    _delay_ms(5000);
    // Log a possibilité d'avoir un 3ième argument
    // qui permet d'éviter de faire un saut à la ligne
    // de façon automatique.
    Logger::log(Priority::INFO, "Coucou les potes");
}
```

