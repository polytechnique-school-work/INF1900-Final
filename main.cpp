#define F_CPU 8000000UL
#include "Light/LightManager.hpp"
#include "Wheel/WheelManager.hpp"
#include "Timer/TimerManager.hpp"
#include "PWM/Pwm.hpp"
#include <util/delay.h>

int main() {
    TimerManager::runTimer(50);
    while(true) {
        if(TimerManager::isDone()) {
           // Faire action
        }
    }
}
