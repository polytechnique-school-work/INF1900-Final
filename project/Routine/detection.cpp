#include "detection.hpp"
#include "FetchRoutine.hpp"
#include "robot/Robot.hpp"

void RoutineDetection::loopSound() {
    SoundPlayer sp;
    sp.init();

    for (int i = 0; i < 3; i++) {
        sp.playSound(45);
        _delay_ms(300);
        sp.reset();
        _delay_ms(300);
    }
}

void RoutineDetection::sonGrave(uint8_t note) {
    SoundPlayer sp;
    sp.init();

    sp.playSound(note);
    _delay_ms(1000);
    sp.reset();
}

void RoutineDetection::flashRed() {
    LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

    while (true) {
        lm.setLight(Color::RED);
        _delay_ms(250);
        lm.setLight(Color::OFF);
        _delay_ms(250);
    }
}

void RoutineDetection::flashAmber() {
    LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);

    while (true) {
        for (int k = 0; k < 12; k++) {
            lm.setLight(Color::AMBER);
        }
        lm.setLight(Color::OFF);
        _delay_ms(250);
    }
}

void RoutineDetection::executeRoutine(Robot& robot) {
    LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1);
    RoutineSteps routineSteps = RoutineSteps::START;
    ExternInterrupt::init(InterruptType::RISING_EDGE, Button::FIRST);
    ExternInterrupt::init(InterruptType::FALLING_EDGE, Button::SECOND);
    uint8_t headDirection     = 0; // Temporairement set, pas la vraie value
    FetchRoutine fetchRoutine = FetchRoutine();

    while (true) {
        switch (routineSteps) {
            case RoutineSteps::START:
                Logger::log(Priority::INFO, "Début de la routine");
                // 1.Light Amber
                while (true) {
                    lm.setLight(Color::AMBER);

                    if (ExternInterrupt::getInterruptCount(Button::FIRST) > 0) {
                        Logger::log(Priority::INFO, "Choix du robot: Haut de la table");
                        routineSteps = RoutineSteps::INT_CLICKED;
                        ExternInterrupt::resetInterruptCount(Button::FIRST);
                        break;
                    }

                    else if (ExternInterrupt::getInterruptCount(Button::SECOND) > 0) {
                        Logger::log(Priority::INFO, "Choix du robot: Droite de la table");
                        routineSteps = RoutineSteps::WHITE_CLICKED;
                        ExternInterrupt::resetInterruptCount(Button::SECOND);
                        break;
                    }
                }

                break;

            case RoutineSteps::INT_CLICKED:
                // orienté vers le haut
                Logger::log(Priority::INFO, "Changement vers le haut de la table");
                headDirection = 0; // Set la direction choisie.
                lm.setLight(Color::GREEN);
                _delay_ms(2000);
                lm.setLight(Color::OFF);
                // variable différente pour case suivant
                routineSteps = RoutineSteps::FIND_STICK;
                break;

            case RoutineSteps::WHITE_CLICKED:
                // orienté vers la droite
                Logger::log(Priority::INFO, "Changement vers la droite de la table");
                headDirection = 2; // Set la direction chsoisie
                lm.setLight(Color::RED);
                _delay_ms(2000);
                lm.setLight(Color::OFF);
                // variable différente pour case suivant
                routineSteps = RoutineSteps::FIND_STICK;
                break;

            case RoutineSteps::FIND_STICK:
                Logger::log(Priority::INFO, "Lancement de la recherche globale");

                /*
                 *   Lancement de la routine de recherche
                 */
                fetchRoutine.fetchBlocks(robot, headDirection);

                routineSteps = RoutineSteps::WAIT;
                break;

            case RoutineSteps::FOUND_STICK:

                /*
                 *   TODO: Probablement pas vraiment utile
                 */

                Logger::log(Priority::INFO, "Le robot a trouvé le poteau");
                // 5. 3 sons aigus: son (300 ms), pause(300ms) 3x
                loopSound();
                // se dirige vers

                routineSteps = RoutineSteps::WAIT;
                break;

            case RoutineSteps::WAIT:
                Logger::log(Priority::INFO, "Le robot est en attente");
                // 6.clignoter led ambrée à 2Hz -> 2 tours par seconde
                while (true) {
                    flashAmber();

                    // Jusqu'à temps qu'on pèse sur interrupt
                    if (ExternInterrupt::getInterruptCount(Button::FIRST) > 0) {
                        ExternInterrupt::resetInterruptCount(Button::FIRST);
                        routineSteps = RoutineSteps::INT_CLICKED;
                        break;
                    }
                }
                break;

            case RoutineSteps::NO_STICK:
                Logger::log(Priority::INFO, "Aucun poteau n'a été trouvé");
                sonGrave(70);
                _delay_ms(2000);

                flashRed();
                // fin du switch case

                break; // life is sad lick my toes :)
        }
    }
}
