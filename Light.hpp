#include <avr/io.h> 

enum class Color { RED, GREEN, OFF };

class Light {
private:
    volatile uint8_t* regis;
    uint8_t first;
    uint8_t second;

public:
    static Light* instance;
    static Light* getInstance() {
        return instance;
    }

    template <typename... Args>
    void init(volatile uint8_t* regis, uint8_t first, uint8_t second) {
        instance = this;
        this->regis = regis;
        this->first = first;
        this->second = second;
        *regis |= (1 << first) | (1 << second); // On veut set XXXX XX11
    }

    void setLight(Color color) {

        switch (color)
        {
        case Color::GREEN:
            *this->regis |= (1 << this->first);
            *this->regis &= ~(1 << this->second);
            break;
        case Color::RED:
            *this->regis &= ~(1 << this->first);
            *this->regis |= (1 << this->second);
            break;
        case Color::OFF:
            *this->regis &= ~(1 << this->first) | (1 << this->second); 
            break;
        default:
            break;
        }
    }
};