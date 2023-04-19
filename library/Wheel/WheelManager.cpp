#include "WheelManager.hpp"
#include "../PWM/Pwm.hpp"
#include <avr/io.h>

WheelManager::WheelManager(volatile uint8_t* registre, volatile uint8_t* port, uint8_t pinLeft,
                           uint8_t pinRight)
    : registre(registre), port(port), pinLeft(pinLeft), pinRight(pinRight) {
    *this->registre |= (1 << PORTD6) | (1 << PORTD7) | (1 << pinLeft) | (1 << pinRight);
}

void WheelManager::update() {
    Pwm pwm;
    pwm.editValues(this->speed, this->speed);

    switch (this->direction) {
        case Direction::FORWARD:
            this->setWheel(Wheel::LEFT, Direction::FORWARD);
            this->setWheel(Wheel::RIGHT, Direction::FORWARD);
            break;
        case Direction::BACKWARD:
            this->setWheel(Wheel::LEFT, Direction::BACKWARD);
            this->setWheel(Wheel::RIGHT, Direction::BACKWARD);
            break;
        case Direction::LEFT:
            this->setWheel(Wheel::LEFT, Direction::FORWARD);
            this->setWheel(Wheel::RIGHT, Direction::BACKWARD);
            break;
        case Direction::RIGHT:
            this->setWheel(Wheel::LEFT, Direction::BACKWARD);
            this->setWheel(Wheel::RIGHT, Direction::FORWARD);
            break;
        default:
            break;
    }
}

WheelManager WheelManager::setDirection(Direction direction) {
    this->direction = direction;
    return *this;
}

WheelManager WheelManager::setSpeed(uint8_t speed) {
    this->speed = speed;
    return *this;
}

Direction WheelManager::getDirection() const { return this->direction; }

void WheelManager::setWheel(Wheel wheel, Direction direction) {
    switch (wheel) {
        case Wheel::RIGHT:
            switch (direction) {
                case Direction::FORWARD:
                    *this->port &= ~(1 << this->pinRight);
                    break;
                case Direction::BACKWARD:
                    *this->port |= (1 << this->pinRight);
                    break;
                default:
                    break;
            }
            break;
        case Wheel::LEFT:
            switch (direction) {
                case Direction::FORWARD:
                    *this->port &= ~(1 << this->pinLeft);
                    break;
                case Direction::BACKWARD:
                    *this->port |= (1 << this->pinLeft);
                    break;
                default:
                    break;
            }
            break;
    }
};
