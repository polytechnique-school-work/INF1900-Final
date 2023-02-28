#define F_CPU 8000000UL
#include <Logger/Logger.hpp>
#include <util/delay.h>

int main() {
    Logger::init();
    _delay_ms(2000);
    Logger::log(Priority::INFO, "Le robot est démarré.");
}