#define F_CPU 8000000UL
#include "Light/LightManager.hpp"
#include <PWM/Pwm.hpp>
#include <util/delay.h>
#include <Wheel/WheelManager.hpp>

LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

int main() {
    DDRD = 0xFF;
    WheelManager wheels;
    wheels.setDirection(Direction::RIGHT);
    wheels.setSpeed(100);
    wheels.update();
}