#include "FetchRoutine.hpp"
// On obtiens 360 degrés en faisant 8 tours de 45 degrés.
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

    robot.setHeadDirection(HeadDirection::NORTH);

    for (uint8_t i = 0; i < MAX_TURN; i++) {
        // Set a left.
        // Au lieu de renvoyer un boolean, je vais devoir renvoyer un Enum si NON_TROUVÉ, PREMIER ou
        // DEUXIÈME à moins qu'on le récupère par après.
        bool hasFind = magicWheels.turn(startDirection);
        if (hasFind) {
            magicWheels.stopMoves();

            uint16_t distance = robot.getSensor().readValue();

            magicWheels.moveForward();
            uint16_t actualDistance = distance;

            // Avance jusqu'à temps qu'il soit suffisamment près.
            while (actualDistance > MAXMIMAL_DISTANCE_ACCEPTED) {
                actualDistance = robot.getSensor().readValue();
            }

            magicWheels.stopMoves();

            // TODO : Trouver un moyen d'envoyer les coordonnées du bloc trouvé.

            this->findedBlock(robot);
        }
    }
}

/*
    Fait toute l'opération pour dire que le block est trouvé.
*/
void FetchRoutine::findedBlock(Robot robot, FindedBlock findedBlock) {
    /*
        - Écriture en mémoire de la coordonnée.
        - Lancement de la procédure de fin.
    */

    this->writeCoordonateInMemory(Robot robot, FindedBlock findedBlock);

    for (uint8_t i = 0; i < 3; i++) {
        robot.getSoundPlayer().playSound(22);
        _delay_ms(300);
        robot.getSoundPlayer().reset();
        _delay_ms(300);
    }
}

void FetchRoutine::writeCoordonateInMemory(Robot robot, FindedBlock findedBlock) {}

void FetchRoutine::fetchBlocks(Robot robot, Direction startDirection) {
    // Je vais devoir savoir ou on est rendu dans notre recherche.

    // 8 correspond au nombre maximum de blocs à trouver.
    for (uint8_t i = 0; i < 8; i++) {

        fetchBlock(robot, );
    }
}