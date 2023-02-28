#define F_CPU 8000000UL
#include <Logger/Logger.hpp>
#include <util/delay.h>

int main() {
    Logger::init();
    _delay_ms(5000);
    // Log a possibilité d'avoir un 3ième argument
    // qui permet d'éviter de faire un saut à la ligne
    // de façon automatique.
    Logger::log(Priority::INFO, "Coucou les potes");
}