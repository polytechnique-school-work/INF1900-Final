

#define F_CPU 8000000UL
#include "Light.hpp"

#include <avr/delay.h>

int main() {
    Light::init();
    Light::setLight(Color::GREEN);
}