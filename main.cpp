#define F_CPU 8000000UL
#include "Light/LightManager.hpp"
#include "Wheel/WheelManager.hpp"
#include "Timer/TimerManager.hpp"
#include "PWM/Pwm.hpp"
#include "Logger/Logger.hpp"
#include <util/delay.h>

LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

int main() {

    // DDRA = 0xFF;
    // DDRD = 0xFF;
    // TimerManager::runTimer(50);

    // while(true) {
    //     if(TimerManager::isDone()) {
    //        lm.setLight(Color::GREEN);
    //     }
    // }

    Logger::init();
    while(true) {
        Logger::log(Priority::INFO, "Coucou les potes");
    }

}
