#pragma once
#include <avr/io.h>

// Utilise le timer 0 afin de pouvoir utiliser la PWM des roues ET une minuterie en même temps.

int notes[36] = {
4545,
4290,
4050,
3822,
3608,
3405,
3214,
3034,
2863,
2703,
2551,
2408,
2273,
2145,
2025,
1911,
1804,
1703,
1607,
1517,
1432,
1351,
1276,
1204,
1136,
1073,
1012,
956,
902,
851,
804,
758,
716,
676,
638,
602,
568
}

class SoundPlayer {
private:
public:
    void init();
    void playSound(Note note, int activeTime, int period);
    void reset();
};