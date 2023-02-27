#pragma once
#include <avr/io.h> 
enum class Direction {
    FORWARD, BACKWARD, RIGHT, LEFT
};

enum class Wheel {
    RIGHT, LEFT
};

class WheelManager {
private:
    uint8_t speed;
    Direction direction;
    void setWheel(Wheel wheel, Direction direction);
public:
    WheelManager setDirection(Direction direction);
    WheelManager setSpeed(uint8_t speed);
    void update();
};