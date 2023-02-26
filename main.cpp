#define F_CPU 8000000UL
#include "Light/LightManager.hpp"
#include <util/delay.h>

LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

int main() {
    lm.setLight(Color::RED);
    _delay_ms(500);
    for(;;) {
        lm.setLight(Color::AMBER);
    }
}
