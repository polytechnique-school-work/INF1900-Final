#include "Translator.hpp"
void Translator::translate(WheelManager& roues, LightManager& lumiere) {
    this->wheels = wheels;
    this->light  = light;

    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    this->maxIndex = (values[0] << 8U) | values[1];

    uint8_t instruction = 0U;
    uint8_t arg         = 0U;

    for (this->index = 2; this->index < this->maxIndex; this->index += 2U) {
        DEBUG_PRINT(("INDEX"));
        DEBUG_PRINT((this->index));
        // DEBUG_PRINT((this->index));
        memory.lecture(this->index, &instruction);
        _delay_ms(100);
        memory.lecture(this->index + 1U, &arg);
        _delay_ms(100);
        // Exécute chacune des instructions
        DEBUG_PRINT(("INSTRUCTION"));
        DEBUG_PRINT((instruction));
        DEBUG_PRINT(("ARGUMENT"));
        DEBUG_PRINT((arg));
        //  this->execute(instruction, arg);
    }

    // DEBUG_PRINT((this->index));
    // DEBUG_PRINT((this->maxIndex));
}

void Translator::execute(uint8_t instruction, uint8_t arg) {
    bool isActive = false;

    Mnemonic mnemonic = static_cast<Mnemonic>(instruction);

    if (isActive != true && mnemonic != Mnemonic::DBT) return;

    switch (mnemonic) {
        case Mnemonic::DBT: // Début
            DEBUG_PRINT(("DEBUT"));
            isActive = true;
            break;

        case Mnemonic::ATT: // Attendre
            for (uint8_t i = 0; i < arg; i++)
                _delay_ms(25);
            break;

        case Mnemonic::DAL: // Allumer la del
            DEBUG_PRINT(("LIGHT"));
            Color color;
            switch (arg) {
                case 1:
                    color = Color::GREEN;
                    break;

                case 2:
                    color = Color::RED;
                    break;

                default:
                    break;
            }
            this->light->setLight(color);
            break;
        case Mnemonic::DET: // Éteindre la del
            this->light->setLight(Color::OFF);
            break;

        case Mnemonic::SGO: // Jouer une sonorité
            /* code */
            break;

        case Mnemonic::SAR: // Arrêter de jouer la sonorité
            /* code */
            break;

        case Mnemonic::MAR1: // Arrêter les moteurs 1
        case Mnemonic::MAR2: // Arrêter les moteurs 2
            this->wheels->setSpeed(0);
            break;

        case Mnemonic::MAV: // Avancer
            this->wheels->setDirection(Direction::FORWARD);
            this->wheels->setSpeed(arg * 100 / 255);
            break;

        case Mnemonic::MRE: // Reculer
            this->wheels->setDirection(Direction::BACKWARD);
            this->wheels->setSpeed(arg * 100 / 255);
            break;

        case Mnemonic::TRD: // Tourner à droite
            this->wheels->setDirection(Direction::RIGHT);
            this->wheels->setSpeed(arg * 100 / 255);
            break;

        case Mnemonic::TRG: // Tourner à gauche
            this->wheels->setDirection(Direction::LEFT);
            this->wheels->setSpeed(arg * 100 / 255);
            break;

        case Mnemonic::DBC: // Début de boucle
            this->loopIndex   = index + 2;
            this->loopCounter = arg;
            break;

        case Mnemonic::FBC: // Fin de la boucle
            if (this->loopCounter > 0) {
                this->loopCounter--;
                index = this->loopIndex;
            }
            break;

        case Mnemonic::FIN: // Fin
            isActive = false;
            return;

        default:
            break;
    }
}