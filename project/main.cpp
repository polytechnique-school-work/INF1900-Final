/*
 * Utilité : Fichier de base du projet
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
#define F_CPU 8000000UL
// #include <util/delay.h>
// #include "SoundPlayer/SoundPlayer.hpp"
// #include "Translator/Translator.hpp"
// #include <Light/LightManager.hpp>
// #include <Logger/Logger.hpp>

#include <Light/LightManager.hpp>
#include <util/delay.h>
#include <Memory/memoire_24.h>
#include <Logger/Logger.hpp>

// WheelManager wheels = WheelManager(&DDRD, &PORTD, PORTD4, PORTD5);
LightManager light  = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
static const uint16_t STARTUP_DELAY = 2000;


// void init() {
//     _delay_ms(STARTUP_DELAY);
//     Logger::log(Priority::INFO, "Le programme est lancé.");
//     DEBUG_PRINT(("Le programme est lancé."));
// }

void init() {
    // 2400 bauds
    // Format des trames: 8 bits, 1 stop bits, sans parité

    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Receiver enable RXEN0 : 1
    // UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

}

void transmitUSART(uint8_t data) {
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

int main() {

    init();
    light.setLight(Color::GREEN);
    //init();
    light.setLight(Color::RED);



    // this->wheels = &wheels;
    // this->light = &light;

    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    //DEBUG_PRINT((values[0]));
    //DEBUG_PRINT((values[1]));

    uint16_t maxIndex = 0;
    maxIndex = (uint16_t(values[0]) << 8) | values[1]; // OK

    uint8_t instruction = 0;
    uint8_t arg         = 0;
    uint16_t index = 0;

    for (index = 2; index < maxIndex; index += 2) {
        memory.lecture(index, &instruction);
        _delay_ms(100);
        memory.lecture(index + 1, &arg);
        _delay_ms(100);

        //transmitUSART(instruction);

        DEBUG_PRINT((instruction));
        //DEBUG_PRINT(("INSTRUCTION"));
        //DEBUG_PRINT((instruction));
        // DEBUG_PRINT(("LOOP")); 
        //this->execute(instruction, arg);
    }
    


    // Translator translator = Translator();
    // translator.translate(wheels, light);
   
    //DEBUG_PRINT(("Hello"));

    //light.setLight(Color::GREEN);
    return 0;
}