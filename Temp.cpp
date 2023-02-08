/*

    Quand la carte mère démarre, la DEL libre doit s'allumer en rouge. 

    Si le bouton-poussoir libre pour usage général est pesé, la DEL 

    affiche la couleur ambre. Quand le bouton-poussoir est relâché, 

    la DEL devient verte. Si le bouton est de nouveau pesé, la DEL prend 

    la couleur rouge encore. Quand il est relâché, la DEL s'éteint. Si le 

    bouton est de nouveau pesé, la DEL affiche la couleur verte. Quand il 

    est relâché, la DEL tourne au rouge ce qui fait que la carte mère est 

    de retour à son état initial et tout peut recommencer.

* 

* Description tirée du problème 2 dans https://cours.polymtl.ca/inf1900/tp/tp2/

+--------------+--------+------------+--------+

| État Initial | Entrée | État Futur | Sortie |

+--------------+--------+------------+--------+

| INIT         | 0      | INIT       | Rouge  |

+--------------+--------+------------+--------+

| INIT         | 1      | APPUI_1    | Ambre  |

+--------------+--------+------------+--------+

| APPUI_1      | 0      | PREMIER    | Vert   |

+--------------+--------+------------+--------+

| APPUI_1      | 1      | APPUI_1    | Ambre  |

+--------------+--------+------------+--------+

| PREMIER      | 0      | PREMIER    | Vert   |

+--------------+--------+------------+--------+

| PREMIER      | 1      | APPUI_2    | Rouge  |

+--------------+--------+------------+--------+

| APPUI_2      | 0      | DEUXIEME   | 0      |

+--------------+--------+------------+--------+

| APPUI_2      | 1      | APPUI_2    | Rouge  |

+--------------+--------+------------+--------+

| DEUXIEME     | 0      | DEUXIEME   | 0      |

+--------------+--------+------------+--------+

| DEUXIEME     | 1      | APPUI_3    | Vert   |

+--------------+--------+------------+--------+

| APPUI_3      | 0      | INIT       | Rouge  |

+--------------+--------+------------+--------+

| APPUI_3      | 1      | APPUI_3    | Vert   |

+--------------+--------+------------+--------+

* Dans cette table d'états, les APPUI_X correspondent

* aux boucles while(PIND & D2). En effet, elles représentent l'état

* où on garde le bouton enfoncé.

*

* Dans ce programme, nous utilisons: 

* Entrées : D2 pour le contrôle du bouton.

* Sorties : A0 et A1 pour contrôler la LED.

*

* Auteurs : Gabriel Landry et Thomas Petrie

* Date: 16 janvier 2023

*/

#define F_CPU 8000000UL

#include <avr/io.h> 

#include <avr/delay.h>

#include <avr/interrupt.h>

#define AMBER_GREEN_DELAY 12

#define AMBER_RED_DELAY 5

#define D2 0x04

#define A0_A1 0b11

enum LIGHT { GREEN = 0x01, RED = 0x02, AMBER = 0x04, OFF = 0x00 };

enum PINS { IN = 0x00, OUT = 0xff };


volatile uint8_t gMinuterieExpiree;

volatile uint8_t isAlreadyStarted;

volatile uint8_t gBoutonPoussoir; 

void lightGreen() {
    PORTA |= (1 << PORTA0);
    PORTA &= ~(1 << PORTA1);
}

void lightRed() {
    PORTA &= ~(1 << PORTA0);
    PORTA |= (1 << PORTA1);
}

void lightOff() {
    PORTA &= ~(A0_A1);
}

void partirMinuterie ( uint16_t duree ) {
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0; // Ici on met le début du compteur.
    OCR1A = duree; // En gros ici on met le nombre maximum à atteindre
    TCCR1A = 0;
    //'modifier ici';
    TCCR1B = (1<<CS10) | (1<<CS12) | (1 << WGM12); // Explication page 629 de la documentation, mais en gros ça met le bit 2 et le bit 0 à 1, pour avoir le tout /1024 (normalement).
    //'modifier ici';
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
    //'modifier ici';
}

void init() {
    gMinuterieExpiree = 0;
    isAlreadyStarted = 0;

    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli();

    DDRD &= ~(1 << D2);

    DDRA |= (A0_A1);

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00);
 
    // sei permet de recevoir à nouveau des interruptions.

    sei();

    lightOff();
}


ISR (TIMER1_COMPA_vect) {
   gMinuterieExpiree += 1;
}

ISR (INT0_vect) {
    gBoutonPoussoir = 1;
    _delay_ms (30);
    //'modifier ici'
}

int main() {
    init();
    partirMinuterie(65536);

    while(true) {
        // Attente de 10 secondes
        if(gMinuterieExpiree == 1 && isAlreadyStarted != 1) {
            partirMinuterie(12589);
            isAlreadyStarted = 1;
        }

        //Attente de 1/10 secondes
        if(gMinuterieExpiree == 2 && isAlreadyStarted != 2) {
            lightRed();
            partirMinuterie(781);
            isAlreadyStarted = 2;
        }

        if(gMinuterieExpiree == 3) {
            lightOff();
            break;
        }
    }

    partirMinuterie(7812);
    

    do {

    } while (gMinuterieExpiree == 3 && gBoutonPoussoir == 0);


    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli ();

    // Verifier la réponse
    if(gBoutonPoussoir == 1) {
        lightGreen();
    }

    else if(gMinuterieExpiree == 4) {
        lightRed();
    }
    


}