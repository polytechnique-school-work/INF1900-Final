#include "robot/Robot.hpp"
#include <Wheel/WheelManager.hpp>
class MagicalWheels {

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

private:
    uint32_t moveTimestamp; // Timestamp qui sera changé à chaque déplacement.
    Robot robot;

public:
    MagicalWheels(Robot r) : robot(r) {}
};