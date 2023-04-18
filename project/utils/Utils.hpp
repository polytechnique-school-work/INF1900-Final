#pragma once
#define F_CPU = 8000000UL
#include <util/delay.h>

namespace Utils {
    void wait(uint16_t value) {
        for (uint16_t i = 0; i < value; i++) {
            _delay_ms(100);
        }
    }
}