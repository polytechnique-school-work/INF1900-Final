#include "Pwm.hpp"

void Pwm::update() {
    const static uint8_t MAX_VALUE = 255;

    // Permet mettre la valeur supposée entre 0 et 100 pour
    // qu'elle soit exprimée entre 0 et 255.
    OCR1A = uint8_t(MAX_VALUE * (float(this->firstPwm) / 100));
    OCR1B = uint8_t(MAX_VALUE * (float(this->secondPwm) / 100));

    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
}

void Pwm::editValue(PwmValues pwmValues, uint8_t value, bool update) {
    pwmValues == PwmValues::FIRST ? this->firstPwm = value : this->secondPwm = value;
    if (update) this->update();
}

void Pwm::editValues(uint8_t first, uint8_t second) {
    Pwm::editValue(PwmValues::FIRST, first, false);
    Pwm::editValue(PwmValues::SECOND, second, false);
    this->update();
}