#include "ExternInterrupt.hpp"
static volatile uint8_t interruptCount = 0;
static constexpr uint8_t DEBOUNCE_DELAY = 30;
static bool lastClick = true;
static ClickType lastClickType = ClickType::NONE;

void ExternInterrupt::init(InterruptType interruptType){
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli();

    // Port D2 utilisé pour les interruptions.
    DDRD &= ~(1 << PORTD2);

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    switch (interruptType) {
    case InterruptType::ANY:
        EICRA |= (1 << ISC00);
        break;
    case InterruptType::FALLING_EDGE:
        EICRA |= (1 << ISC01);
    case InterruptType::RISING_EDGE:
        EICRA |= (1 << ISC00) | (1 << ISC01);;
    default:
        break;
    }

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

volatile uint8_t ExternInterrupt::getInterruptCount() {
    return interruptCount;
}

void ExternInterrupt::resetInterruptCount() {
    interruptCount = 0;
}

ClickType ExternInterrupt::getLastClickType() {
    return lastClickType;
}

ClickType ExternInterrupt::getClickType() {
    return lastClickType == ClickType::UNCLICK ? ClickType::CLICK : ClickType::UNCLICK;
}
const char* ExternInterrupt::convertClickTypeToString(ClickType clickType) {
    switch (clickType) {
        case ClickType::CLICK:
            return "click";
        case ClickType::UNCLICK:
            return "unclick";
        case ClickType::NONE:
            return "none";
        default:
            return "";
        }
}

ISR (INT0_vect) {
    bool actualClick = !(PIND & (1 << PORTD2));
    if(actualClick != lastClick) {
        _delay_ms(DEBOUNCE_DELAY);
        if(actualClick != lastClick) {
            actualClick ? lastClickType = ClickType::CLICK : lastClickType = ClickType::UNCLICK;
            lastClick = actualClick;
            ++interruptCount;
        }
    }
}

