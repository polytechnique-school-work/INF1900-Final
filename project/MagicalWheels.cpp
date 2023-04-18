#include "MagicalWheels.hpp"
#include "Constantes.hpp"
#include "utils/Utils.hpp"

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

    uint32_t stopTime = Clock::getTimestamp() + TURN_DURATION;

    while (Clock::getTimestamp() < stopTime) {
        // Faire en sorte que si le fetch a une certaine valeur de retour, on skip le while (et on
        // effectue pas le change direction).
        uint16_t hasFindSomething = this->fetch(direction);
        if (hasFindSomething <= SECOND_DISTANCE) {
            DEBUG_PRINT(("Fin de la rotation (45) : trouvé."));
            DEBUG_PRINT((hasFindSomething));
            return hasFindSomething;
        }
    }

    this->stopMoves();

    _delay_ms(1000);

    changeDirection(direction);

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

void MagicalWheels::changeDirection(Direction direction) {
    if (direction != Direction::LEFT && direction != Direction::RIGHT) {
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

void MagicalWheels::moveForward() {
    this->robot.getWheelManager()->setDirection(Direction::FORWARD);
    this->robot.getWheelManager()->setSpeed(ROBOT_SPEED);
    this->robot.getWheelManager()->update();
}