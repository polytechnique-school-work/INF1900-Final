#include "Pwm.hpp"
#define F_CPU 8000000UL

void Pwm::update() {
    const static uint8_t MAX_VALUE = 255;

    // Permet mettre la valeur supposée entre 0 et 100 pour
    // qu'elle soit exprimée entre 0 et 255.
    OCR2A = uint8_t(MAX_VALUE * (float(this->firstPwm) / 100));
    OCR2B = uint8_t(MAX_VALUE * (float(this->secondPwm) / 100));

    TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
    TCCR2B = (1 << CS22) | (1 << CS20);
}

void Pwm::editValue(PwmValue pwmValue, uint8_t value, bool update) {
    pwmValue == PwmValue::FIRST ? this->firstPwm = value : this->secondPwm = value;
    if (update) this->update();
}

void Pwm::editValues(uint8_t first, uint8_t second) {
    Pwm::editValue(PwmValue::FIRST, first * 1.05, false); // Droite
    Pwm::editValue(PwmValue::SECOND, second, false);      // Gauche
    this->update();
}