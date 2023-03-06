#define F_CPU 8000000UL
#include <Logger/Logger.hpp>
#include <util/delay.h>
#include <ExternInterrupt/ExternInterrupt.hpp>

static const uint16_t STARTUP_DELAY = 2000;

// Met en place les systèmes utiles.
void init() {
    Logger::init();
    _delay_ms(STARTUP_DELAY);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}


int main() {
    DEBUG_PRINT((5));

}