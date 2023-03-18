#define F_CPU 8000000UL
#include "Writer.hpp"
#include <Logger/Logger.hpp>
#include <util/delay.h>
int main() {
    _delay_ms(2000);
    DEBUG_PRINT(("Lancé"));

    Writer writer;
    writer.receive();
}