#include "MagicalWheels.hpp"
#include "robot/Robot.hpp"
class FetchRoutine {
public:
    // Devra retourner les coordonnées.
    // Prend en paramètre la direction de départ.
    void fetchBlock(Robot robot, Direction startDirection);
    void findedBlock(Robot robot);
};