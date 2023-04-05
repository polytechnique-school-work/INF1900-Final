#define F_CPU 8000000UL
#include "transmission.hpp"

void Emetteur::ExecuteRoutine()
{
    Color color = Color::GREEN; // if 0 light off, if i light green
    uint32_t previousTimestamp = clock.getTimeStamp();
    uint8_t byte;
    uint32_t crc = 0xFFFFFFFF; 

    Logger::transmitUSART(0x02);

    for(uint16_t i = 0; i < SVG.tailleTotale; i++){
        memory.lecture(i, &byte)
        crc = crc ^ byte;
        for ( int k = 8; k; k-- ) {
            if(crc & 1) {
                crc = (crc >> 1) ^ DIVISOR; 
            }
            else {
                crc = (crc >> 1); 
            }
        }

        Logger::transmitUSART(byte);
        if (clock.getTimeStamp() > previousTimestamp + 5){
            if(color == Color::OFF){
                this->light->setLight(Color::GREEN);
                color = Color::GREEN;
            }
            else{
                this->light->setLight(Color::OFF);
                color = Color::OFF;
            }
            previousTimestamp = clock.getTimeStamp();
        }
            
    }
    Logger::transmitUSART(0x03);
    crc = crc ^ 0xFFFFFFFF;
    uint8_t crc32[4];
    crc32[0] = uint8_t(crc);
    crc32[1] = uint8_t(crc << 8);
    crc32[2] = uint8_t(crc << 16);
    crc32[3] = uint8_t(crc << 24);   
    Logger::transmitMessage(crc32);
    Logger::transmitUSART(0x04);
        
}