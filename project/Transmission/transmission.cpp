#define F_CPU 8000000UL

#include "transmission.hpp"

void Emetteur::ExecuteRoutine()
{
    LightManager light = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
    light.setLight(Color::GREEN);

    Clock clock;
    clock.init();

    _delay_ms(2000);

    uint8_t indices[6] = {8, 9, 26, 30, 16, 13};
    SVG svg = SVG(clock, light);

    for(uint8_t i : indices){
        svg.visiterPoint(i);
    }


    Logger::init();

    Logger::transmitUSART(0x02);

    svg.transmitSVG();
    
    Logger::transmitUSART(0x03);
    
    svg.crc = svg.crc ^ 0xFFFFFFFF;
    char crc32[8];

    sprintf(crc32, "%lx", svg.crc);

    for (char octet: crc32){
        Logger::transmitUSART(octet);
    }

    Logger::transmitUSART(0x04);

    light.setLight(Color::OFF); 
}