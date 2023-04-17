// #pragma once
// #include <Light/LightManager.hpp>
// #include "SVG/Structures.hpp"
// #include <Logger/Logger.hpp>
// #include <Memory/memoire_24.h>
// #include <Clock/Clock.hpp>
// #include <avr/io.h>
// #include <util/delay.h>

// class Emetteur
// {
// public :
//     Emetteur(LightManager &lm, Memoire24CXXX memory, Clock &clock, SVG &svg)
//     {
//         this-> light = &lm;
//         this-> memory = &memory;
//         this-> clock = &clock;
//         this-> svg = &svg;
//     };
//     void ExecuteRoutine();

//     void flashGreen();

// private :
//     LightManager* light  = nullptr;
//     Memoire24CXXX* memory = nullptr;
//     Clock* clock = nullptr;
//     SVG* svg = nullptr;
// };