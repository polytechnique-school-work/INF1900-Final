#include <avr/io.h> 

enum class Color { RED, GREEN, OFF };

class Light {
public:
    static void init() {
        // Initialisation des sorties pour les lumières.
        DDRA |= (1 << PORTA0) | (1 << PORTA1); // On veut set XXXX XX11
    }

    static void setLight(Color color) {
        switch (color)
        {
        case Color::GREEN:
            PORTA |= (1 << PORTA0);
            PORTA &= ~(1 << PORTA1);
            break;
        case Color::RED:
            PORTA &= ~(1 << PORTA0);
            PORTA |= (1 << PORTA1);
            break;
        case Color::OFF:
            PORTA &= ~(1 << PORTA0) | (1 << PORTA1); 
            break;
        default:
            break;
        }
    }
};