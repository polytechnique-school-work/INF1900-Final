#include "MagicalWheels.hpp"
#include "robot/Robot.hpp"
enum class FindedBlock { UNDEFINED, FIRST, SECOND };
class FetchRoutine {
public:
    // Devra retourner les coordonnées.
    // Prend en paramètre la direction de départ.
    FindedBlock fetchBlock(Robot robot, uint8_t blockCount);
    void findedBlock(Robot robot, FindedBlock findedBlock);
    void writeCoordonateInMemory(Robot robot, FindedBlock findedBlock);
    void fetchBlocks(Robot robot, HeadDirection startDirection);
};