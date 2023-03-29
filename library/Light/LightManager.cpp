#define F_CPU 8000000UL
#include <util/delay.h>
#include "Light/LightManager.hpp"

LightManager::LightManager(volatile uint8_t* registre, volatile uint8_t* port, uint8_t pinFirst, uint8_t pinSecond):
    regis(registre),
    firstPin(pinFirst),
    secondPin(pinSecond),
    port(port)
    {
        // Initialisation
        // Permet de définir le port en sortie ou en entrée.
        *registre |= (1 << pinFirst) | (1 << pinSecond);
    }

void LightManager::setLight(Color color) {
   
    switch (color)
    {
        case Color::GREEN:
            *port |= (1 << this->firstPin);
            *port &= ~(1 << this->secondPin);
            break;
        case Color::RED:
            *port &= ~(1 << this->firstPin);
            *port |= (1 << this->secondPin);
            break;
        case Color::AMBER:
            setLight(Color::GREEN);
            _delay_ms(this->DelayGREEN);
            setLight(Color::RED);
            _delay_ms(this->DelayRED);
            break;
        case Color::OFF:
            *port &= ~(1 << this->secondPin) & ~(1 << this->firstPin); 
            break;
        default:
            break;
    }
}