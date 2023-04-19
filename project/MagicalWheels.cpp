#include "MagicalWheels.hpp"
#include "Constantes.hpp"
#include "utils/Utils.hpp"

uint16_t MagicalWheels::turn(Direction direction) {

    DEBUG_PRINT(("Début du tour"));

    if (direction != Direction::LEFT && direction != Direction::RIGHT) {
        DEBUG_PRINT(("Impossible de faire tourner le robot avec cette direction."));
        return 0;
    }

    changeDirection(direction);
    // On met un arrêt avec un delay pour éviter les problèmes d'inerties.
    stopMoves();

    uint32_t stopTime = Clock::getTimestamp() + TURN_DURATION;

    // uint8_t counter = 0;

    while (Clock::getTimestamp() < stopTime) {

        // WheelManager* wheelManager = this->robot.getWheelManager();
        // uint32_t moveDuration      = Clock::getTimestamp() + START_DURATION;
        // wheelManager->setDirection(direction);
        // wheelManager->setSpeed(80);
        // wheelManager->update();
        // while (Clock::getTimestamp() < moveDuration) {
        //     Logger::log(Priority::INFO, "Start loop");
        // }

        // uint32_t stopDuration = Clock::getTimestamp() + STOP_DURATION;
        // wheelManager->setDirection(direction);
        // wheelManager->setSpeed(0);
        // wheelManager->update();
        // while (Clock::getTimestamp() < stopDuration) {
        //     Logger::log(Priority::INFO, "Stop loop");
        // }

        // Faire en sorte que si le fetch a une certaine valeur de retour, on skip le while (et on
        // effectue pas le change direction).
        uint16_t hasFindSomething = this->fetch(direction);
        if (hasFindSomething <= SECOND_DISTANCE) {
            DEBUG_PRINT(("Fin de la rotation (45) : trouvé."));
            DEBUG_PRINT((hasFindSomething));
            return hasFindSomething;
        }

        wheelManager->setDirection(direction);
        wheelManager->setSpeed(0);
        wheelManager->update();

        /*
         *   Vérification si on voit un poteau ou pas.
         */
        // Vers la même direction
        uint32_t duration = Clock::getTimestamp() + CHECK_BLOCK_DURATION;
        wheelManager->setDirection(direction);
        wheelManager->setSpeed(ROBOT_SPEED);
        wheelManager->update();
        while (Clock::getTimestamp() < duration) {
            if (hasFindSomething <= SECOND_DISTANCE) {
                DEBUG_PRINT(("Fin de la rotation (45) : trouvé."));
                DEBUG_PRINT((hasFindSomething));
                return hasFindSomething;
            }
        }

        // Vers la direction inverse
        Direction directionInverse =
            direction == Direction::RIGHT ? Direction::RIGHT : Direction::LEFT;
        duration = Clock::getTimestamp() + CHECK_BLOCK_DURATION;
        wheelManager->setDirection(directionInverse);
        wheelManager->setSpeed(ROBOT_SPEED);
        wheelManager->update();
        while (Clock::getTimestamp() < duration) {
            if (hasFindSomething <= SECOND_DISTANCE) {
                DEBUG_PRINT(("Fin de la rotation (45) : trouvé."));
                DEBUG_PRINT((hasFindSomething));
                // counter++;
                return hasFindSomething;
            }
        }

        return 0;
        // Retour

        // counter++;
    }

    this->stopMoves();

    DEBUG_PRINT(("Fin de la rotation (45) : non trouvé."));
    return 0;
}

void MagicalWheels::stopMoves() {
    this->robot.getWheelManager()->setSpeed(0);
    this->robot.getWheelManager()->update();
    _delay_ms(WAITING_DURATION_BETWEEN_MOVES);
}

uint16_t MagicalWheels::fetch(Direction direction) {

    /*
        TODO
        On doit faire en sorte de vérifier si y'a une valeur en bas d'une certaine valeur à chaque
    fois. Soit qu'on définie une valeur par défaut et il se dirige vers un bloc en dessous d'une
    certaine valeur.
    Vérifier que le bloc est pas trop loin.
    Retourner la distance.
    */
    uint16_t value = this->robot.getSensor()->readValue();
    // DEBUG_PRINT(value);
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

    return newHeadDirection;
}

void MagicalWheels::changeDirection(Direction direction) {
    if (direction != Direction::LEFT && direction != Direction::RIGHT) {
        DEBUG_PRINT(("Impossible de faire tourner le robot avec cette direction."));
        return;
    }

    // Incrémente ou décrémente notre enum
    // HeadDirection newHeadDirection = direction == Direction::LEFT
    //                                      ? incrementHeadDirection(this->robot.getHeadDirection())
    //                                      :
    //                                      decrementHeadDirection(this->robot.getHeadDirection());

    // this->robot.setHeadDirection(newHeadDirection);

    uint8_t actualHeadDirection = this->robot.getHeadDirection();
    uint8_t newHeadDirection;

    this->robot.setHeadDirection(newHeadDirection);

    DEBUG_PRINT(("Changement de la direction"));
}

void MagicalWheels::moveForward() {
    this->robot.getWheelManager()->setDirection(Direction::FORWARD);
    this->robot.getWheelManager()->setSpeed(ROBOT_SPEED);
    this->robot.getWheelManager()->update();
}