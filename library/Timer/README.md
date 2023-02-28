<h1>Gestion de la minuterie</h1>

Ce module permet de gérer une minuterie de type CTC de façon très simplifié.
<hr>
<h2>Exemple d'utilisation</h2>

```c++
#include "TimerManager.hpp"

int main() {
    TimerManager::runTimer(50); // Durée en 0.1 seconde * temps inscrit.
    while(true) {
        if(TimerManager::isDone()) {
           // Faire action
        }
    }
}
```