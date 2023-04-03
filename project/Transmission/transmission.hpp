#pragma once
#include <ExternInterrupt/ExternInterrupt.hpp>
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Wheel/WheelManager.hpp>
#include <PWM/Pwm.hpp>
#include <SoundPlayer/SoundPlayer.hpp>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

enum class TransmissionSteps {START,WAIT,START_TEXTE,END_TEXTE,END}

class RoutineTransmission 
{
public :
    void ExecuteRoutine(); 

private :
    void flashGreen();
};