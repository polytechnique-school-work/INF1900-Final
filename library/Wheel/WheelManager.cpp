#include "WheelManager.hpp"
#include "../PWM/Pwm.hpp"

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

void WheelManager::setWheel(Wheel wheel, Direction direction) {
    switch (wheel) {
        case Wheel::RIGHT:
            switch (direction) {
                case Direction::FORWARD:
                    // TODO Mettre les bonnes variables à set.
                    break;
                case Direction::BACKWARD:
                    // TODO Mettre les bonnes variables à set.
                    break;
                default:
                    break;
            }
            break;
        case Wheel::LEFT:
            switch (direction) {
                case Direction::FORWARD:
                    // TODO Mettre les bonnes variables à set.
                    break;
                case Direction::BACKWARD:
                    // TODO Mettre les bonnes variables à set.
                    break;
                default:
                    break;
            }
            break;
    }
};

