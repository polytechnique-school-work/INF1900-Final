#define F_CPU 8000000UL

#include <avr/io.h> 
#include <avr/delay.h>
#include <avr/interrupt.h>

// Il faudrait que je trouve une solution pour faire en sorte
// de pouvoir recevoir les pings directement dans cette classe
// et d'ensuite les redistribuer.
ISR(TIMER1_COMPA_vect) {
    Timer::
}

enum class TimerType {
    ONCE,
    PWM
};

class Timer {
private:
    TimerType timerType = TimerType::ONCE;

public:
    void runTimer(uint16_t duration, uint16_t startAt) {
        TCNT1 = startAt;
        OCR1A = duration;
        TCCR1A = 0;
        TCCR1B = (1<<CS10) | (1<<CS12) | (1 << WGM12);
        TCCR1C = 0;
        TIMSK1 = (1 << OCIE1A);
    }
    Timer setTimerType(TimerType timerType) {
        this->timerType = timerType;
    }
};