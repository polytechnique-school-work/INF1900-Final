#pragma once
#include <Light/LightManager.hpp>
#include "SVG/Structures.hpp"
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <Clock/Clock.hpp>
#include <avr/io.h> 
#include <util/delay.h>

class Emetteur 
{
public :
    Emetteur()
    {
        
    };
    void ExecuteRoutine(); 

    void flashGreen();

private :
 
};