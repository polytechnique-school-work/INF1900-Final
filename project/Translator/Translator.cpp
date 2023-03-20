#include "Translator/Translator.hpp"
#include "Utils.hpp"

static const uint16_t TURNING_TIME = 550;
static const uint16_t DELAY        = 500;

void Translator::translate(WheelManager& wheels, LightManager& light) {
    this->soundPlayer.init();

    this->wheels = &wheels;
    this->light  = &light;

    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    this->maxIndex = (uint16_t(values[0]) << 8) | values[1]; // OK

    uint8_t instruction = 0;
    uint8_t arg         = 0;

    for (this->index = 2; this->index < this->maxIndex; this->index += 2) {
        memory.lecture(this->index, &instruction);
        memory.lecture(this->index + 1, &arg);

        DEBUG_PRINT(("Instruction"));
        DEBUG_PRINT((instruction));
        this->execute(instruction, arg);
    }
}

void Translator::execute(uint16_t instruction, uint16_t arg) {
    Mnemonic mnemonic = static_cast<Mnemonic>(instruction);

    if (isActive != true && mnemonic != Mnemonic::DBT) return;
    uint8_t speed;
    uint16_t pourcentagePWM;
    Direction direction;

    switch (mnemonic) {
        case Mnemonic::DBT: // Début
            DEBUG_PRINT(("BEGIN"));
            isActive = true;
            break;

        case Mnemonic::ATT: // Attendre
            DEBUG_PRINT(("ATTENDRE"));
            for (uint8_t i = 0; i < arg; i++)
                _delay_ms(25);
            break;

        case Mnemonic::DAL: // Allumer la del
            DEBUG_PRINT(("LIGHT ON"));
            Color color;
            switch (arg) {
                case 1:
                    color = Color::GREEN;
                    break;

                case 2:
                    color = Color::RED;
                    break;
                default:
                    // ne fait rien
                    break;
            }
            this->light->setLight(color);
            break;
        case Mnemonic::DET: // Éteindre la del
            DEBUG_PRINT(("LIGHT OFF"));
            this->light->setLight(Color::OFF);
            break;

        case Mnemonic::SGO: // Jouer une sonorité
            DEBUG_PRINT(("PLAY SOUND"));
            this->soundPlayer.playSound(arg);
            break;

        case Mnemonic::SAR: // Arrêter de jouer la sonorité
            DEBUG_PRINT(("STOP SOUND"));
            this->soundPlayer.reset();
            break;

        case Mnemonic::MAR1: // Arrêter les moteurs 1
        case Mnemonic::MAR2: // Arrêter les moteurs 2
            DEBUG_PRINT(("STOP MOTORS"));
            this->wheels->setSpeed(0);
            this->wheels->update();
            break;

        case Mnemonic::MAV: // Avancer
            DEBUG_PRINT(("MOVE FORWARD"));
            this->wheels->setDirection(Direction::FORWARD);
            this->wheels->setSpeed(arg * 100 / 255);
            this->wheels->update();
            break;

        case Mnemonic::MRE: // Reculer
            DEBUG_PRINT(("MOVE BACKWARD"));
            this->wheels->setDirection(Direction::BACKWARD);
            this->wheels->setSpeed(arg * 100 / 255);
            this->wheels->update();
            break;

        case Mnemonic::TRD:         // Tourner à droite
            speed          = OCR2A; // Sur 255
            pourcentagePWM = speed / 255 * 100;
            direction      = this->wheels->getDirection();
            this->wheels->setSpeed(0);
            Utils::wait(DELAY);
            DEBUG_PRINT(("TURN RIGHT"));
            this->wheels->setDirection(Direction::RIGHT);
            this->wheels->setSpeed(speed * 100 / 255);
            this->wheels->update();
            Utils::wait(TURNING_TIME / pourcentagePWM / 100);
            this->wheels->setSpeed(speed * 100 / 255);
            this->wheels->setDirection(direction);
            this->wheels->update();
            break;
        case Mnemonic::TRG: // Tourner à gauche
            DEBUG_PRINT(("TURN LEFT"));

            speed          = OCR2A; // Sur 255
            pourcentagePWM = speed / 255 * 100;

            direction = this->wheels->getDirection();

            this->wheels->setDirection(Direction::LEFT);
            this->wheels->setSpeed(speed * 100 / 255);
            this->wheels->update();

            // Attente pour permettre une rotation de 90 degrés
            Utils::wait(TURNING_TIME / pourcentagePWM / 100);

            // Garder la même trajectoire précédente
            this->wheels->setSpeed(speed * 100 / 255);
            this->wheels->setDirection(direction);
            this->wheels->update();
            break;

        case Mnemonic::DBC: // Début de boucle
            DEBUG_PRINT(("START LOOP"));
            this->loopIndex   = index;
            this->loopCounter = arg;
            break;

        case Mnemonic::FBC: // Fin de la boucle
            DEBUG_PRINT(("END LOOP"));
            if (this->loopCounter > 0) {
                this->loopCounter--;
                index = this->loopIndex;
            }
            break;

        case Mnemonic::FIN: // Fin
            DEBUG_PRINT(("END"));
            wheels->setSpeed(0);
            wheels->update();
            light->setLight(Color::OFF);
            isActive = false;
            return;

        default:
            DEBUG_PRINT(("DEFAULT"));
            break;
    }
}