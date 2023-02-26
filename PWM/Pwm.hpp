#pragma once
#include <avr/io.h> 
enum class PwmValues {
    FIRST, SECOND
};

class Pwm {
private:
    // Correspondent respectivement aux pins d5 et d6
    uint8_t firstPwm = 0;
    uint8_t secondPwm = 0;
    // Permet d'update les valeurs de PWM
    void update();

public:
    // Permet d'update une seule valeur
    // Le booléen permet d'indiquer si l'edit value fait l'update ou non,
    // permet surtout d'éviter un écrasement des données fait en double
    // avec le editValues().
    void editValue(PwmValues pwmValues, uint8_t value, bool update = true);

    // Permet d'update plusieurs valeurs
    void editValues(uint8_t first, uint8_t second);
};