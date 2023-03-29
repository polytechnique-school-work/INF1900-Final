#include "MagicalWheels.hpp"
#include "utils/Utils.hpp"

void MagicalWheels::turn(Direction direction) {
    if (direction != Direction::LEFT || direction != Direction::RIGHT) {
        DEBUG_PRINT(("Impossible de faire tourner le robot avec cette direction."));
        return;
    }

    // On met un arrêt avec un delay pour éviter les problèmes d'inerties.
    stopMoves();

    const uint32_t TURN_DURATION = 200;
    WheelManager wheelManager    = this->robot.getWheelManager();
    wheelManager.setDirection(direction);
    wheelManager.setSpeed(this->robot.getSpeed());
    wheelManager.update();

    uint32_t stopTime = Clock::getTimestamp() + TURN_DURATION;

    while (Clock::getTimestamp() < stopTime) {
        // Faire en sorte que si le fetch a une certaine valeur de retour, on skip le while (et on
        // effectue pas le change direction).
        this->fetch();
    }

    this->stopMoves();

    changeDirection(direction);
}

void MagicalWheels::stopMoves() {
    this->robot.getWheelManager().setSpeed(0);
    Utils::wait(this->robot.getWaitTurnDuration());
}

void MagicalWheels::fetch() {

    /*
        TODO
    */
}

void MagicalWheels::changeDirection(Direction direction) {
    if (direction != Direction::LEFT || direction != Direction::RIGHT) {
        DEBUG_PRINT(("Impossible de faire tourner le robot avec cette direction."));
        return;
    }

    // Incrémente ou décrémente notre enum
    HeadDirection newHeadDirection =
        static_cast<HeadDirection>(static_cast<uint8_t>(this->robot.getHeadDirection()) +
                                   (direction == Direction::RIGHT ? -1 : 1));
    this->robot.setHeadDirection(newHeadDirection);
    DEBUG_PRINT(("Changement de la direction"));
}