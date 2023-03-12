#define F_CPU 8000000UL
#include <Logger/Logger.hpp>
#include <util/delay.h>
#include <ExternInterrupt/ExternInterrupt.hpp>

static const uint16_t STARTUP_DELAY = 2000;

// Met en place les systèmes utiles.
void init() {
    _delay_ms(STARTUP_DELAY);
    Logger::log(Priority::INFO, "Le programme est lancé.");
}

int main() {
    init();
    ExternInterrupt::init(InterruptType::ANY);
    uint8_t value = 0;
    while(true){
        if(ExternInterrupt::getInterruptCount() > value) {
            value = ExternInterrupt::getInterruptCount();
            Logger::log(Priority::INFO, "Interruption détectée");
            ClickType clickType = ExternInterrupt::getLastClickType();
            const char* type = ExternInterrupt::convertClickTypeToString(clickType);
            Logger::log(Priority::INFO, type);
        }
    }
}