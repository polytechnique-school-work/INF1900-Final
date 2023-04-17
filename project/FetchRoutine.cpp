#include "FetchRoutine.hpp"
#include <ExternInterrupt/ExternInterrupt.hpp>
#include <Memory/memoire_24.h>
// On obtiens 360 degrés en faisant 8 tours de 45 degrés.
static const uint8_t MAX_TURN                   = 8;
static const uint16_t MINIMAL_DISTANCE_ACCEPTED = 150;
static const uint16_t FIRST_DISTANCE            = 220;
static const uint16_t SECOND_DISTANCE           = 250;

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
        uint16_t hasFind = magicWheels.turn(Direction::RIGHT);
        FindedBlock findedBlock;
        if (hasFind != 0) {

            magicWheels.stopMoves();

            magicWheels.moveForward();
            uint16_t actualDistance = hasFind;

            Direction direction = Direction::RIGHT;

            // Avance jusqu'à temps qu'il soit suffisamment près.
            while (actualDistance > MINIMAL_DISTANCE_ACCEPTED) {

                // Actualiser la distance actuelle
                actualDistance = robot.getSensor()->readValue();

                /*
                 *   Retrouver la valeur si elle est perdue
                 */
                // Si la distance est rendu plus grande que celle anciennement trouvée.
                if (actualDistance > hasFind) {

                    // Faire changer la direction pour retrouver le hasFind.
                    direction =
                        (direction == Direction::RIGHT ? Direction::LEFT : Direction::RIGHT);

                    robot.getWheelManager()->setDirection(direction);
                    robot.getWheelManager()->setSpeed(robot.getSpeed());
                    robot.getWheelManager()->update();

                    while (actualDistance > hasFind) {

                        // Actualiser la valeur pour pouvoir effectuer la comparaison.
                        actualDistance = robot.getSensor()->readValue();
                    }
                }

                // Continuer à avancer jusqu'à quitter le while.
                robot.getWheelManager()->setDirection(Direction::FORWARD);
                robot.getWheelManager()->setSpeed(robot.getSpeed());
                robot.getWheelManager()->update();
            }

            Logger::log(Priority::INFO, "Bloc trouvé à une distance de: ", actualDistance);

            magicWheels.stopMoves();
            _delay_ms(1000);

            if (hasFind < FIRST_DISTANCE)
                findedBlock = FindedBlock::FIRST;
            else if (hasFind < SECOND_DISTANCE)
                findedBlock = FindedBlock::SECOND;

            // TODO : Trouver un moyen d'envoyer les coordonnées du bloc trouvé.
        } else {
            DEBUG_PRINT("UNDEFINED");
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
    if (findedBlock == FindedBlock::UNDEFINED) {
        return; // Faire quelque chose de spécial si rien de trouvé.
    }

    this->writeCoordonateInMemory(robot, findedBlock);

    for (uint8_t i = 0; i < 3; i++) {
        robot.getSoundPlayer()->playSound(30);
        _delay_ms(300);
        robot.getSoundPlayer()->reset();
        _delay_ms(300);
    }

    /*
     *   Bloquer le robot d'avancer, attente du click
     */

    ExternInterrupt::init(InterruptType::RISING_EDGE, Button::FIRST);
    ExternInterrupt::resetInterruptCount(Button::FIRST);
    while (true) {

        robot.getLightManager()->setLight(Color::AMBER);

        // Cliquer sur le bouton interrupt
        if (ExternInterrupt::getInterruptCount(Button::FIRST) > 0) {
            Logger::log(Priority::INFO, "Prochain poteau");
            break;
        }
    }
}

void FetchRoutine::writeCoordonateInMemory(Robot robot, FindedBlock findedBlock) {

    /*
     *   Changer la position du robot.
     */
    int8_t first  = 0;
    int8_t second = 0;

    int8_t relatives[2] = {0, 0};

    switch (robot.getHeadDirection()) {
        case HeadDirection::NORTH:
            relatives[0] = 0;
            relatives[1] = 1;
            break;
        case HeadDirection::NORTHEAST:
            relatives[0] = 1;
            relatives[1] = 1;
            break;
        case HeadDirection::EAST:
            relatives[0] = 1;
            relatives[1] = 0;
            break;
        case HeadDirection::SOUTH_EAST:
            relatives[0] = 1;
            relatives[1] = -1;
            break;
        case HeadDirection::SOUTH:
            relatives[0] = 0;
            relatives[1] = -1;
            break;
        case HeadDirection::SOUTHWEST:
            relatives[0] = -1;
            relatives[1] = -1;
            break;
        case HeadDirection::WEAST:
            relatives[0] = -1;
            relatives[1] = 0;
            break;
        case HeadDirection::NORTHWEST:
            relatives[0] = -1;
            relatives[1] = 1;
            break;

        default:
            break;
    }

    int8_t multValue = (findedBlock == FindedBlock::FIRST ? 1 : 2);

    relatives[0] *= multValue;
    relatives[1] *= multValue;

    // Changement des coordonnées du robots.
    robot.setX(robot.getX() + relatives[0]);
    robot.setY(robot.getY() + relatives[1]);

    // Write ces coordonnées en mémoire.
    Memoire24CXXX memoire = Memoire24CXXX();

    memoire.ecriture(robot.getMemoryCount(), robot.getX());
    memoire.ecriture(robot.getMemoryCount() + 1, robot.getY());

    DEBUG_PRINT(("Coordonnées du robot"));
    DEBUG_PRINT((robot.getX()));
    DEBUG_PRINT((robot.getY()));

    robot.incrementMemoryCount();

    // Doit être relatif à sa position.
}

void FetchRoutine::resetMemory() {
    Memoire24CXXX memory = Memoire24CXXX();

    for (uint8_t i = 0; i < 16; i++) {
        memory.ecriture(i, 255);
    }
}

/*
 *   Exécute la routine de recherche de bloc le nombre de fois nécessaire.
 */
void FetchRoutine::fetchBlocks(Robot robot, HeadDirection startDirection) {

    resetMemory();

    // 8 correspond au nombre maximum de blocs à trouver.
    for (uint8_t i = 0; i < 8; i++) {
        // set la direction en fonction de soit c'est la première étape, soit c'est au north.

        Logger::log(Priority::INFO, "Exécution de recherche");

        if (i != 0) startDirection = HeadDirection::NORTH;
        fetchBlock(robot, i);
    }
}