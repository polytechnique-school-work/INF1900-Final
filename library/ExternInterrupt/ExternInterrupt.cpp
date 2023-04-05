#include "ExternInterrupt.hpp"
static volatile uint8_t interruptCountFirst = 0;
static bool lastClickFirst                  = true;
static ClickType lastClickTypeFirst         = ClickType::NONE;
static InterruptType interruptFirst;

static constexpr uint8_t DEBOUNCE_DELAY      = 50;
static volatile uint8_t interruptCountSecond = 0;
static bool lastClickSecond                  = true;
static ClickType lastClickTypeSecond         = ClickType::NONE;
static InterruptType interruptSecond;

void ExternInterrupt::init(InterruptType interruptType, Button button) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli();

    // Port D2 utilisé pour les interruptions.
    DDRD &= ~(1 << (button == Button::FIRST ? PORTD2 : PORTD3));

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << (button == Button::FIRST ? INT0 : INT1));

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    button == Button::FIRST ? interruptFirst = interruptType : interruptSecond = interruptType;
    switch (interruptType) {
        case InterruptType::ANY:
            EICRA |= (1 << (button == Button::FIRST ? ISC00 : ISC10)) ;
            break;
        case InterruptType::FALLING_EDGE:
            EICRA |= (1 << (button == Button::FIRST ? ISC01 : ISC11));
            break;
        case InterruptType::RISING_EDGE:
            EICRA |= (1 << (button== Button::FIRST ? (1 << ISC00) | (1 << ISC01) : (1 << ISC10) | (1 << ISC11)));
            break;
        default:
            break;
    }

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

volatile uint8_t ExternInterrupt::getInterruptCount(Button button) {
    return button == Button::FIRST ? interruptCountFirst : interruptCountSecond;
}

void ExternInterrupt::resetInterruptCount(Button button) {
    button == Button::FIRST ? interruptCountFirst = 0 : interruptCountSecond = 0;
}

ClickType ExternInterrupt::getLastClickType(Button button) {
    return (button == Button::FIRST ? lastClickTypeFirst : lastClickTypeSecond);
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

ISR(INT0_vect) {
    // Permet de recalculer à chaque fois
    auto actual = []() { return (PIND & (1 << PORTD2)); };

    // Si ce n'est pas un ANY, on fait en sorte que
    // lastClick devient l'inverse du click.
    if (interruptFirst != InterruptType::ANY) lastClickFirst = !(actual());

    // Si le click est toujours pareil (donc l'inverse de lastClick), on rentre.
    if (actual() != lastClickFirst) {
        _delay_ms(DEBOUNCE_DELAY);
        // Si le click est toujours le même après X ms, on élimine
        // la possiblité d'un rebondissement.
        if (actual() != lastClickFirst) {
            // On edit le lastClickType de façon à inscrire
            // le type du click actuel.
            lastClickFirst     = actual();
            lastClickTypeFirst = actual() ? ClickType::CLICK : ClickType::UNCLICK;
            interruptCountFirst++;
        }
    }
}

ISR(INT1_vect) {
    // Permet de recalculer à chaque fois
    auto actual = []() { return (PIND & (1 << PORTD3)); };

    // Si ce n'est pas un ANY, on fait en sorte que
    // lastClick devient l'inverse du click.
    if (interruptSecond != InterruptType::ANY) lastClickSecond = !(actual());

    // Si le click est toujours pareil (donc l'inverse de lastClick), on rentre.
    if (actual() != lastClickSecond) {
        _delay_ms(DEBOUNCE_DELAY);
        // Si le click est toujours le même après X ms, on élimine
        // la possiblité d'un rebondissement.
        if (actual() != lastClickSecond) {
            // On edit le lastClickType de façon à inscrire
            // le type du click actuel.
            lastClickSecond     = actual();
            lastClickTypeSecond = actual() ? ClickType::CLICK : ClickType::UNCLICK;
            interruptCountSecond++;
        }
    }
}
