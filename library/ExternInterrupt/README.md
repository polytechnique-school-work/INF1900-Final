<h1>Gestion des interruptions externes</h1>

Ce module permet de détecter des interruptions qui sont effecutées
sur le port `D2`.

Il est possible de récupérer plusieurs éléments.

`getLastClickType()` : Permet de récupérer le type du dernier click.
'None' dans le cas où aucun click n'a été effectué.

`getClickType()` : Permet de récupérer le click actuel. En fait, c'est juste l'inverse du `getLastClickType()`. Dans le cas où c'est 'None', ce sera le type **Click**.

`convertClickTypeToString()` : Permet de convertir un type en __*const char**__.

`getInterruptCount()` : Permet de récupérer le compte du nombre d'interruptions effectuées depuis le début (ou depuis le dernier reset). Ce compte d'interruptions augmente de 1 à chaque intéraction.

<h2>Les différentes méthodes</h2>

`init()` : Permet d'initialiser la gestion des interruptions selon plusieurs modes décrit dans la page 68 de la documentation [**AVRLibC**](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf).

`resetInterruptCount()` : Permet de remettre à 0 le compte d'interruptions.


## Limitation

Malheureusement, en utilisant le système en ANY, lorsqu'on clique et relâche très rapidement le bouton, celui-ci détecte seulement 2x un unclick. Je n'arrive pas à trouver pourquoi.

<hr>
<h2>Exemple d'utilisation</h2>

```cpp
#define F_CPU 8000000UL
#include <Logger/Logger.hpp>
#include <util/delay.h>
#include <ExternInterrupt/ExternInterrupt.hpp>

void init() {
    _delay_ms(STARTUP_DELAY);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {
    init();
    ExternInterrupt::init(InterruptType::ANY);
    uint8_t value = 0;
    while(true){
        if(ExternInterrupt::getInterruptCount() > value) {
            value = ExternInterrupt::getInterruptCount();
            Logger::log(Priority::INFO, "Interruption détectée");
            ClickType clickType = ExternInterrupt::getLastClickType();
            const char* type = ExternInterrupt::convertClickTypeToString(clickType);
            Logger::log(Priority::INFO, type);
        }
    }
}
```

