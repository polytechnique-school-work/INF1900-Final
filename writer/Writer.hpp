#pragma once
#include <Memory/memoire_24.h>
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
class Writer {
public:
    void receive();

private:
    unsigned char receiveUSART();
    void initReceiveUSART();
};