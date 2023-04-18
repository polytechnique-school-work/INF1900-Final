#pragma once
#include "SVG/Structures.hpp"
#include <Clock/Clock.hpp>
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <avr/io.h>
#include <util/delay.h>

class Emetteur {
public:
    Emetteur(){

    };
    void ExecuteRoutine();

    void flashGreen();

private:
};