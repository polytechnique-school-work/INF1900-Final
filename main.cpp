#define F_CPU 8000000UL
#include "Logger/Logger.hpp"
#include <util/delay.h>
#include "ExternInterrupt/ExternInterrupt.hpp"

int main() {
    Logger::init();
    _delay_ms(5000);
    Logger::log(Priority::INFO, "Le programme est lancé.");
    ExternInterrupt::init(InterruptType::ANY);
    uint8_t value = 0;
    while(true){
        if(ExternInterrupt::getInterruptCount() > value) {
            value = ExternInterrupt::getInterruptCount();
            Logger::log(Priority::INFO, "Interruption détectée");
            Logger::log(Priority::INFO, ExternInterrupt::convertClickTypeToString(ExternInterrupt::getClickType()));
        }
    }
}
