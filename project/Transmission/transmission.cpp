#define F_CPU 8000000UL

#include "transmission.hpp"

void Emetteur::ExecuteRoutine()
{
    Memoire24CXXX memory;

    LightManager light = LightManager(&DDRA, &PORTA, PORTA0, PORTA1);
    light.setLight(Color::GREEN);

    Clock clock;
    clock.init();

    _delay_ms(2000);

    uint8_t x[8];
    uint8_t y[8];
    uint8_t iteration = 0;

    {uint8_t buffer;
    
    for(; iteration < 8; iteration++)
    {
        memory.lecture(iteration*2, &buffer);
        if(buffer != 255){
            x[iteration] = buffer;
        }
        else{
            break;
        }
        memory.lecture(iteration*2 + 1, &buffer);
        if(buffer != 255){
            y[iteration] = buffer;
        }
        else{
            break;
        }
    }}


    uint8_t indices[iteration];

    for(uint8_t i = 0; i < iteration; i++){
        indices[i] = x[i] + y[i]* 8 + 1;
    }

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