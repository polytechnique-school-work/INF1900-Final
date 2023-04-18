#include "Executer.hpp"
#include "Routine/detection.hpp"

void Executer::executeRoutine(Robot& robot) {

    ExternInterrupt::init(InterruptType::RISING_EDGE, Button::FIRST);
    ExternInterrupt::init(InterruptType::FALLING_EDGE, Button::SECOND);

    while (true) {

        if (ExternInterrupt::getInterruptCount(Button::FIRST) > 0) {
            Logger::log(Priority::INFO, "Démarrage en détection");
            ExternInterrupt::resetInterruptCount(Button::FIRST);
            RoutineDetection routineDetection = RoutineDetection();
            routineDetection.executeRoutine(robot);
            break;
        }

        else if (ExternInterrupt::getInterruptCount(Button::SECOND) > 0) {
            Logger::log(Priority::INFO, "Démarrage en transmission");
            ExternInterrupt::resetInterruptCount(Button::SECOND);

            /*
             * TODO : Exécution transmission
             */

            break;
        }
    }

    Logger::log(Priority::INFO, "Robot - Terminé");
}