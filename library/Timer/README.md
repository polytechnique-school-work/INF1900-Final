<h1>Gestion de la minuterie</h1>

Ce module permet de gérer une minuterie de type CTC de façon très simplifiée.
<hr>

## Différentes méthodes

`isDone()` : Permet de vérifier si le dernier timer lancé est terminé.

`isChecked()` : Permet de vérifier si le dernier timer lancé a été vérifié (seulement lorsqu'il est terminé).

`runTimer(uint16_t durée)` : Permet de lancer un timer. Le temps en paramètre est en 0.1 seconde.

<h2>Exemple d'utilisation</h2>

```c++
#include <Timer/TimerManager.hpp>
#include <Logger/Logger.hpp>

int main() {
    // Permet de générer un timer de 0.1 * 50 secondes (donc 5 secondes).
    TimerManager::runTimer(50);

    Logger::init();
    while(true) {
    // On regarde si le timer est terminé ET si la vérification
    // a déjà été effectuée (pour éviter de log plusieurs fois).
    if(TimerManager::isDone() && !TimerManager::isChecked()) {
        Logger::log(Priority::INFO,"Le timer est terminé.");
    }
   }
}
```