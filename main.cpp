#define F_CPU 8000000UL
#include "Light.hpp"

#include <avr/delay.h>

Light *Light::instance = nullptr;

int main() {
    Light light;
    light.init(&DDRA, 6, 7);
}