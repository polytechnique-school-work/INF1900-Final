#pragma once
// #define F_CPU 8000000UL
#include <ExternInterrupt/ExternInterrupt.hpp>
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Wheel/WheelManager.hpp>
#include <PWM/Pwm.hpp>
#include <SoundPlayer/SoundPlayer.hpp>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

enum class RoutineSteps {START, INT_CLICKED, WHITE_CLICKED, FIND_STICK, FOUND_STICK, WAIT, NO_STICK };

class RoutineDetection
{
public:
    void executeRoutine();

private:
    void flashAmber();
    void flashRed();
    void loopSound();
    void sonGrave();
    
};