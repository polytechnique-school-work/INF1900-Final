#include "Pwm.hpp"
#define F_CPU 8000000UL

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

void Pwm::editValue(PwmValue pwmValue, uint8_t value, bool update) {
    pwmValue == PwmValue::FIRST ? this->firstPwm = value : this->secondPwm = value;
    if (update) this->update();
}

void Pwm::editValues(uint8_t first, uint8_t second) {
    Pwm::editValue(PwmValue::FIRST, first, false);
    Pwm::editValue(PwmValue::SECOND, second, false);
    this->update();
}