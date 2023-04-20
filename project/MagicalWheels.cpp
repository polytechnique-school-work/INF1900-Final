#include "MagicalWheels.hpp"
#include "Constantes.hpp"
#include "utils/Utils.hpp"
uint16_t MagicalWheels::bothVerification(Direction direction) {

    // Première vérification
    uint16_t valueFinded = this->verification(direction);
    // Logger::log(Priority::INFO, valueFinded);
    if (valueFinded != 0) return valueFinded;

    this->stopMoves();

    // Direction inverse
    Direction inverseDirection = direction == Direction::RIGHT ? Direction::LEFT : Direction::RIGHT;
    valueFinded                = this->verification(inverseDirection);
    if (valueFinded != 0) return valueFinded;

    return valueFinded;
}

uint16_t MagicalWheels::verification(Direction direction) {
    uint8_t addValue          = direction == Direction::LEFT ? 5 : 0;
    uint32_t verificationTime = Clock::getTimestamp() + CHECK_BLOCK_DURATION + addValue;
    // Verification d'une certaine durée.
    WheelManager* wheelManager = this->robot.getWheelManager();
    wheelManager->setDirection(direction);
    wheelManager->setSpeed(ROBOT_SPEED);
    wheelManager->update();
    while (Clock::getTimestamp() < verificationTime) {
        uint16_t hasFoundSomething = this->fetch(direction);
        if (hasFoundSomething <= SECOND_DISTANCE) {
            stopMoves();
            return hasFoundSomething;
        }
    }

    this->stopMoves();

    return 0; // Rien trouvé.
}

uint16_t MagicalWheels::turn(Direction direction) {

    DEBUG_PRINT(("Début du tour"));

    if (direction != Direction::LEFT && direction != Direction::RIGHT) {
        DEBUG_PRINT(("Impossible de faire tourner le robot avec cette direction."));
        return 0;
    }

    // On met un arrêt avec un delay pour éviter les problèmes d'inerties.
    stopMoves();

    WheelManager* wheelManager = this->robot.getWheelManager();
    wheelManager->setDirection(direction);
    wheelManager->setSpeed(ROBOT_SPEED);
    wheelManager->update();

    uint32_t stopTime     = Clock::getTimestamp() + TURN_DURATION;
    uint32_t middleTime   = Clock::getTimestamp() + TURN_DURATION / 2;
    bool isAlreadyChanged = false;

    while (Clock::getTimestamp() < stopTime) {
        // Faire en sorte que si le fetch a une certaine valeur de retour, on skip le while (et on
        // effectue pas le change direction).

        if (Clock::getTimestamp() >= middleTime && !isAlreadyChanged) {
            isAlreadyChanged = true;
            // Logger::log(Priority::INFO, "CHANGED");
            robot.setHeadDirection(changeHeadDirection(robot.getHeadDirection(), direction));
        }

        uint16_t hasFindSomething = this->fetch(direction);
        if (hasFindSomething <= SECOND_DISTANCE) {
            DEBUG_PRINT(("Fin de la rotation (45) : trouvé."));
            DEBUG_PRINT((hasFindSomething));
            stopMoves();
            return hasFindSomething;
        }
    }

    this->stopMoves();

    uint16_t valu = bothVerification(direction);
    if (valu != 0) {
        DEBUG_PRINT(("Fin de la rotation (45) : trouvé."));
        stopMoves();
        return valu;
    }

    DEBUG_PRINT(("Fin de la rotation (45) : non trouvé."));
    return 0;
}

void MagicalWheels::stopMoves() {
    this->robot.getWheelManager()->setSpeed(0);
    this->robot.getWheelManager()->update();
    _delay_ms(WAITING_DURATION_BETWEEN_MOVES);
}

uint16_t MagicalWheels::fetch(Direction direction) {
    uint16_t value = this->robot.getSensor()->readValue();
    return value;
}

uint8_t MagicalWheels::changeHeadDirection(uint8_t actualHeadDirection, Direction direction) {

    uint8_t newHeadDirection;
    if (actualHeadDirection == 7 && direction == Direction::RIGHT) {
        newHeadDirection = 0;
    } else if (actualHeadDirection == 0 && direction == Direction::LEFT) {
        newHeadDirection = 7;
    } else {
        if (direction == Direction::RIGHT) {
            newHeadDirection = ++actualHeadDirection;
        } else {
            newHeadDirection = --actualHeadDirection;
        }
    }
    // Logger::log(Priority::INFO, "HeadDirection");
    // Logger::log(Priority::INFO, newHeadDirection);
    return newHeadDirection;
}

void MagicalWheels::moveForward() {
    this->robot.getWheelManager()->setDirection(Direction::FORWARD);
    this->robot.getWheelManager()->setSpeed(ROBOT_SPEED);
    this->robot.getWheelManager()->update();
}