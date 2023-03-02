#define F_CPU 8000000UL
#include "Light/LightManager.hpp"
#include <PWM/Pwm.hpp>
#include <util/delay.h>
#include <Wheel/WheelManager.hpp>

LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

int main() {
    DDRD = 0xFF;
    // Pwm pwm;
    // pwm.editValues(100, 100);
    // // port à 0 = avancer
    // // port à 1 = reculer
    // // orange 8
    // // noir 7
    // PORTD |= (1 << PORTD6) | (1 << PORTD7);

    // _delay_ms(5000);
    // PORTD &= ~((1 << PORTD6) | (1 << PORTD7));

    // _delay_ms(5000);
    // pwm.editValues(50, 50);
    
    WheelManager wheels;
    wheels.setDirection(Direction::RIGHT);
    wheels.setSpeed(100);
    wheels.update();
}