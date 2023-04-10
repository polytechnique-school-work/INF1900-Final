#include "MagicalWheels.hpp"
#include "utils/Utils.hpp"

static const uint32_t TURN_DURATION = 50;

bool MagicalWheels::turn(Direction direction) {

    DEBUG_PRINT(("Début du tour."));

    if (direction != Direction::LEFT && direction != Direction::RIGHT) {
        DEBUG_PRINT(("Impossible de faire tourner le robot avec cette direction.     sdsd"));
        return false;
    }

    // On met un arrêt avec un delay pour éviter les problèmes d'inerties.
    stopMoves();

    WheelManager* wheelManager = this->robot.getWheelManager();
    wheelManager->setDirection(direction);
    wheelManager->setSpeed(this->robot.getSpeed());
    wheelManager->update();

    uint32_t stopTime = Clock::getTimestamp() + TURN_DURATION;

    while (Clock::getTimestamp() < stopTime) {
        // Faire en sorte que si le fetch a une certaine valeur de retour, on skip le while (et on
        // effectue pas le change direction).
        bool hasFindSomething = this->fetch(direction);
        if (hasFindSomething) {
            DEBUG_PRINT(("Fin de la rotation (45) : trouvé."));
            return true;
        }
    }

    this->stopMoves();

    changeDirection(direction);

    DEBUG_PRINT(("Fin de la rotation (45) : non trouvé."));
    return false;
}

void MagicalWheels::stopMoves() {
    this->robot.getWheelManager()->setSpeed(0);
    Utils::wait(this->robot.getWaitTurnDuration());

    // Calculer le déplacement.
    // Pas certain du truc par contre... ça me parait deg comme façon de faire.
    this->robot.calculateMove(this->moveTimestamp);
}

bool MagicalWheels::fetch(Direction direction) {

    /*
        TODO
        On doit faire en sorte de vérifier si y'a une valeur en bas d'une certaine valeur à chaque
       fois. Soit qu'on définie une valeur par défaut et il se dirige vers un bloc en dessous d'une
       certaine valeur.
       Vérifier que le bloc est pas trop loin.
       Retourner la distance.
    */
    return true; // Permettre la compilation.
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
    this->stopMoves();
    this->robot.getWheelManager()->setDirection(Direction::FORWARD);
    this->robot.getWheelManager()->setSpeed(this->robot.getSpeed());
    this->robot.getWheelManager()->update();
}