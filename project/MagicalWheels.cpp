#include "MagicalWheels.hpp"

MagicalWheels::turn(Direction direction) {
    if (direction != Direction::LEFT || direction != Direction::RIGHT) {
        DEBUG_PRINT(("Impossible de faire tourner le robot avec cette direction."));
        return;
    }

    const uint32_t TURN_DURATION = 200;
    WheelManager wheelManager    = this->robot.getWheelManager();
    wheelManager.setDirection(direction);
    wheelManager.setSpeed(this->robot.getSpeed());
    wheelManager.update();

    uint32_t stopTime = Clock::getTimestamp() + TURN_DURATION;

    while (Clock::getTimestamp() < stopTime) {
        this->fetch();
    }

    changeDirection(direction);
}
