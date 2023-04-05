#pragma once
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <Clock/Clock.hpp>
#include <avr/io.h> 
#include <util/delay.h>

class Emetteur 
{
public :
    Emetteur(LightManager &lm, Memoire24CXXX memory, Clock &clock)
    {
        this-> light = &lm;
        this-> memory = &memory;
        this-> clock = &clock;
    };
    void ExecuteRoutine(); 

    void flashGreen();

    void ecritureMemoire(uint8_t taille){
        tailleTotale += taille;
        adresse += taille;
    }

    uint16_t getAdresse(){
        return adresse; 
    }

private :
    LightManager* light  = nullptr;
    Memoire24CXXX* memory = nullptr;
    Clock* clock = nullptr;
    uint16_t adresse;
    uint16_t tailleTotale;
};