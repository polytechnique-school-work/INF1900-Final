<h1>Gestion des lumières</h1>

<h2>Différentes couleurs possibles</h2>


| Couleur | Code           |
|---------|----------------|
| Ambre   | `Color::AMBER` |
| Rouge   | `Color::RED`   |
| Vert    | `Color::GREEN` |

Concernant la couleur ambre, celle-ci est seulement effective un certain temps et si elle n'est pas dans une boucle, elle changera de couleur et sera rouge.

<hr>
<h2>Exemple d'utilisation</h2>

```cpp
#define F_CPU 8000000UL
#include "LightManager.hpp"
#include <util/delay.h>

// Il est important d'initialiser le LightManager de
// façon à ce qu'il soit accessible à l'intérieur du
// scope (le mettre en variable global est accepté).
LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

int main() {
    lm.setLight(Color::RED);
    _delay_ms(500);
    for(;;) {
        lm.setLight(Color::AMBER);
    }
}
```

