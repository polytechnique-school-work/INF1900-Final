<h1>Gestion de la mémoire</h1>

Ce module permet la gestion de la mémoire externe PC de la carte mère. La classe Memoire24CXXX
gère toutes les opérations mémoire (protocole I^2C).

⚠️ Le protocole I^2C réclame l'utilisation des broches C0 et C1 ainsi qu'un cavalier sur MemEN sur la carte mère pour l'échange des données.
<hr>

## Méthodes importantes
`lecture(const uint16_t adresse, uint8_t *donnee)` : Permet la lecture de données à une certaine adresse une donnée à la fois

`lecture(const uint16_t adresse, uint8_t *donnee, const uint8_t longueur)` : Permet la lecture de données à une certaine adresse par bloc de données. ATTENTION: la longueur doit être de 127 ou moins!!!


`ecriture(const uint16_t adresse, const uint8_t donnee)` : Permet l'écriture de données vers une certaine adresse une donnée à la fois

`ecriture(const uint16_t adresse, uint8_t *donnee, const uint8_t longueur)`: Permet l'écriture de données vers une certaine adresse par bloc de données. ATTENTION: la longueur doit être de 127 ou moins!!!

<h2>Exemple d'utilisation</h2>

```cpp
//TP5 pb3
#define F_CPU 8000000
#define DDR_IN 0x00
#define DDR_OUT 0xff
#include <avr/io.h> 
#include <util/delay.h> 
#include "memoire_24.h"
Memoire24CXXX memoire;
//uint16_t ADRESSE = 0x0000;
void initialisationUART (void) {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0               
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1 << UCSZ01)|(1 << UCSZ00);
}
void transmissionUART ( uint8_t donnee ) {
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = donnee;
}
int main()
{
    uint8_t chaine[21] = "Le robot en INF1900\n";
    uint8_t ptr[21];
    memoire.ecriture(0x0000, chaine, 21);
    _delay_ms(10);
    memoire.lecture(0x0000, ptr, 21);
    initialisationUART();
    uint8_t i, j;
    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            transmissionUART ( ptr[j] );
        }
    }
}
```
