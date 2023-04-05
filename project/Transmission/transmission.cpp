#define F_CPU 8000000UL
#define DIVISOR 0xEDB88320

#include "transmission.hpp"

void Emetteur::ExecuteRoutine()
{
    Color color = Color::GREEN; // if 0 light off, if i light green
    this->light->setLight(Color::GREEN);
    _delay_ms(2000);
    uint32_t previousTimestamp = clock->getTimestamp();
    uint8_t byte;
    uint32_t crc = 0xFFFFFFFF; 

    for(char octet : "0x02"){
        Logger::transmitUSART(octet);
    }

    for(uint16_t i = 0; i < tailleTotale; i++){
        memory->lecture(i, &byte);
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
        if (clock->getTimestamp() > previousTimestamp + 5){
            if(color == Color::OFF){
                this->light->setLight(Color::GREEN);
                color = Color::GREEN;
            }
            else{
                this->light->setLight(Color::OFF);
                color = Color::OFF;
            }
            previousTimestamp = clock->getTimestamp();
        }
            
    }
     for(char octet : "0x03"){
        Logger::transmitUSART(octet);
    }
    crc = crc ^ 0xFFFFFFFF;
    char crc32[4];
    crc32[0] = uint8_t(crc);
    crc32[1] = uint8_t(crc >> 8);
    crc32[2] = uint8_t(crc >> 16);
    crc32[3] = uint8_t(crc >> 24);  
    for (char octet: crc32){
        Logger::transmitUSART(octet);
    }
     for(char octet : "0x04"){
        Logger::transmitUSART(octet);
    }
    this->light->setLight(Color::OFF); 
}