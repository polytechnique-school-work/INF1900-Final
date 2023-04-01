#include "FetchRoutine.hpp"
static const uint8_t MAX_TURN                    = 8;
static const uint16_t MAXMIMAL_DISTANCE_ACCEPTED = 15;

/*
    On souhaite que cette routine permette de trouver un bloc (les blocs sont les poteaux).
    Donc voici ce qu'elle fait :
        - Rotation de 45 degrés 8 fois afin de faire un 360 degrés.
            Si elle trouve quelque chose (le turn renvoie 1):
                - Avance jusqu'à atteindre le bloc et s'arrête, lance la prochaine procédure.

*/
void FetchRoutine::fetchBlock(Robot robot, Direction startDirection) {

    MagicalWheels magicWheels = MagicalWheels(robot);

    for (uint8_t i = 0; i < MAX_TURN; i++) {
        bool hasFind = magicWheels.turn();
        if (hasFind) {
            magicWheels.stopMoves();

            uint16_t distance = robot.getSensor().readValue();

            magicWheels.moveForward();
            uint16_t actualDistance = distance;

            while (actualDistance > MAXMIMAL_DISTANCE_ACCEPTED) {
                actualDistance = robot.getSensor().readValue();
            }

            magicWheels.stopMoves();

            // TODO : Trouver un moyen d'envoyer les coordonnées du bloc trouvé.

            this->findedBlock(robot);
        }
    }
}

void FetchRoutine::findedBlock(Robot robot) {}