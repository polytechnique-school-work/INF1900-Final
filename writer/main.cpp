#define F_CPU 8000000UL
#include "Writer.hpp"
#include <Logger/Logger.hpp>
#include <util/delay.h>
int main() {
    DEBUG_PRINT(("Lancé"));
    _delay_ms(5000);

    DEBUG_PRINT(("COUCOU"));
    Writer writer;
    writer.receive();
}