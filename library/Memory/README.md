<h1>Gestion de la mémoire</h1>

Ce module permet la gestion de la mémoire externe PC de la carte mère. La classe Memoire24CXXX
gère toutes les opérations mémoire (protocole I^2C), qui réclame l'utilisation des broches C0 et C1
ainsi qu'un cavalier sur MemEN sur la carte mère pour l'échange des données.
<hr>

<h2>Exemple d'utilisation</h2>

```cpp
#define F_CPU 8000000UL
#include <avr/io.h> 
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

void initialiseUART ( void ) {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    // UCSR0A |= (1 << UDRE0);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);//'modifier ici' ;
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Synchrone (1 << UCSZ01) | (1 << UCSZ00) par défaut

}

// Du USART vers le PC
void transmissionUART( uint8_t donnee ) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1 << UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}


void writeRead() {

}

int main() {
    initialiseUART();
    char word[21] = "Le robot en INF1900\n";
    uint8_t i, j;
    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            transmissionUART(word[j]);
        }
    }
}
```
