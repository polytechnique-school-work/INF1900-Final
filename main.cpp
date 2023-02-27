#define F_CPU 8000000UL
#include "Light/LightManager.hpp"
#include "Wheel/WheelManager.hpp"
#include "Timer/TimerManager.hpp"
#include "PWM/Pwm.hpp"
#include "Logger/Logger.hpp"
#include <util/delay.h>

LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

int main() {

    Logger::init();
    _delay_ms(5000);
    Logger::log(Priority::INFO, "Coucou les potes");
}
