#pragma once
// #define F_CPU 8000000UL
#include "robot/Robot.hpp"
#include <ExternInterrupt/ExternInterrupt.hpp>
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <PWM/Pwm.hpp>
#include <SoundPlayer/SoundPlayer.hpp>
#include <Wheel/WheelManager.hpp>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

enum class RoutineSteps {
    START,
    INT_CLICKED,
    WHITE_CLICKED,
    FIND_STICK,
    FOUND_STICK,
    WAIT,
    NO_STICK
};

class RoutineDetection {
public:
    void executeRoutine(Robot& robot);
    void sonGrave(uint8_t note);

private:
    void flashAmber();
    void flashRed();
    void loopSound();
    // void sonGrave();
};