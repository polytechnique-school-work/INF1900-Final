#include "robot/Robot.hpp"
#include <Logger/Logger.hpp>
#include <Wheel/WheelManager.hpp>
class MagicalWheels {

private:
    // Timestamp qui sera changé à chaque déplacement. Et set à 0 si pas en train de se déplacer.
    uint32_t moveTimestamp;
    Robot robot;
    /*
        Fonction de vérification appelée en boucle lorsqu'il tourne.
    */
    uint16_t fetch(Direction direction);

public:
    MagicalWheels(Robot r) : robot(r) {}

    /*
        En gros, cette classe doit permettre de calculer le temps qui s'est passé
        entre le début du déplacement des roues et la fin. Il doit aussi permettre
        en tout temps de pouvoir calculer le déplacement (si désiré).


        Donc on veut une sorte de "proxy" qui permettra de faire les méthodes de
        WheelManager.


        On souhaite :
        Une méthode qui permet de faire des rotations de 45/90 degrés, tout en permettant
        que si on détecte en même temps de tourner un element pas trop loin avec son capteur,
        qu'il entre dans une autre phase : phase de poteau trouvé.

        Une méthode pour faire avancer le robot, pas besoin de faire de méthode pour reculer.
    */

    /*
        Permet de se diriger vers l'avant.
    */
    void moveForward();

    /*
        Permet d'arrêter l'ensemble des déplacements.
    */
    void stopMoves();

    /*
        Permet de changer la direction selon le turn.
    */
    void changeDirection(Direction direction);

    /*
        Permet de faire un déplacement de 45 degrés.
        - Arrête tous les mouvements x temps.
        - Fait son déplacement
        - Arrête tous les mouvements x temps.
        - Change la direction (incrémente ou décrémente).
    */
    uint16_t turn(Direction direction);
};