#include "ExternInterrupt.hpp"
static volatile uint8_t interruptCount = 0;
static constexpr uint8_t DEBOUNCE_DELAY = 50;
static bool lastClick = true;
static ClickType lastClickType = ClickType::NONE;
static InterruptType interrupt;

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
    interrupt = interruptType;
    switch (interruptType) {
    case InterruptType::ANY:
        EICRA |= (1 << ISC00);
        break;
    case InterruptType::FALLING_EDGE:
        EICRA |= (1 << ISC01);
        break;
    case InterruptType::RISING_EDGE:
        EICRA |= (1 << ISC00) | (1 << ISC01);;
        break;
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

    // Permet de recalculer à chaque fois
    auto actual = []() { return (PIND & (1 << PORTD2)); };

    // Si ce n'est pas un ANY, on fait en sorte que 
    // lastClick devient l'inverse du click.
    if(interrupt != InterruptType::ANY) lastClick = !(actual());

    // Si le click est toujours pareil (donc l'inverse de lastClick), on rentre.
    if(actual() != lastClick) {
        _delay_ms(DEBOUNCE_DELAY);
        // Si le click est toujours le même après X ms, on élimine
        // la possiblité d'un rebondissement.
        if(actual() != lastClick) {
            // On edit le lastClickType de façon à inscrire
            // le type du click actuel.
            lastClick = actual();
            lastClickType = actual() ? ClickType::CLICK : ClickType::UNCLICK;
            interruptCount++;
        }
    }
}

