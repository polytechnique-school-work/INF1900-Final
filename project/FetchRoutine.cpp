#include "FetchRoutine.hpp"
// On obtiens 360 degrés en faisant 8 tours de 45 degrés.
static const uint8_t MAX_TURN                    = 8;
static const uint16_t MAXMIMAL_DISTANCE_ACCEPTED = 15;
static const uint16_t FIRST_DISTANCE             = 30;
static const uint16_t SECOND_DISTANCE            = 700;

/*
    On souhaite que cette routine permette de trouver un bloc (les blocs sont les poteaux).
    Donc voici ce qu'elle fait :
        - Rotation de 45 degrés 8 fois afin de faire un 360 degrés.
            Si elle trouve quelque chose (le turn renvoie 1):
                - Avance jusqu'à atteindre le bloc et s'arrête, lance la prochaine procédure.

*/
FindedBlock FetchRoutine::fetchBlock(Robot robot, uint8_t blockCount) {

    MagicalWheels magicWheels = MagicalWheels(robot);

    for (uint8_t i = 0; i < MAX_TURN; i++) {
        // Au lieu de renvoyer un boolean, je vais devoir renvoyer un Enum si NON_TROUVÉ, PREMIER ou
        // DEUXIÈME à moins qu'on le récupère par après.

        // Boucle jusqu'à temps qu'il trouve quelque chose.
        bool hasFind = magicWheels.turn(Direction::RIGHT);
        FindedBlock findedBlock;
        if (hasFind) {
            magicWheels.stopMoves();

            uint16_t distance = robot.getSensor()->readValue();

            magicWheels.moveForward();
            uint16_t actualDistance = distance;

            // Avance jusqu'à temps qu'il soit suffisamment près.
            while (actualDistance > MAXMIMAL_DISTANCE_ACCEPTED) {
                actualDistance = robot.getSensor()->readValue();
            }

            Logger::log(Priority::INFO, "Bloc trouvé à une distance de: ", actualDistance);

            magicWheels.stopMoves();

            if (distance < FIRST_DISTANCE)
                findedBlock = FindedBlock::FIRST;
            else if (distance < SECOND_DISTANCE)
                findedBlock = FindedBlock::SECOND;

            // TODO : Trouver un moyen d'envoyer les coordonnées du bloc trouvé.
        } else {
            findedBlock = FindedBlock::UNDEFINED;
        }

        this->findedBlock(robot, findedBlock);

        return findedBlock;
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
    if (findedBlock == FindedBlock::UNDEFINED)
        return; // Faire quelque chose de spécial si rien de trouvé.

    this->writeCoordonateInMemory(robot, findedBlock);

    for (uint8_t i = 0; i < 3; i++) {
        robot.getSoundPlayer()->playSound(22);
        _delay_ms(300);
        robot.getSoundPlayer()->reset();
        _delay_ms(300);
    }
}

void FetchRoutine::writeCoordonateInMemory(Robot robot, FindedBlock findedBlock) {}

/*
 *   Exécute la routine de recherche de bloc le nombre de fois nécessaire.
 */
void FetchRoutine::fetchBlocks(Robot robot, HeadDirection startDirection) {
    // 8 correspond au nombre maximum de blocs à trouver.
    for (uint8_t i = 0; i < 8; i++) {
        // set la direction en fonction de soit c'est la première étape, soit c'est au north.

        Logger::log(Priority::INFO, "Exécution de recherche", static_cast<uint16_t>(i));

        if (i != 0) startDirection = HeadDirection::NORTH;
        fetchBlock(robot, i);
    }
}