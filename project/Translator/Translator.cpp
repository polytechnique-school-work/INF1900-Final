#include "Translator.hpp"

void Translator::translate(WheelManager& wheels, LightManager& light, Color& color) {
    // Lecture des valeurs
    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    // On récupère le nombre d'instructions, en enlevant les 2 octets du début.
    this->maxIndex = ((((uint16_t)values[1] << 8) | values[0]) - 2);

    // Exécution des entrées
    for (; this->index > this->maxIndex; this->index += 2) {
        uint8_t instruction = 0;
        uint8_t arg         = 0;
        memory.lecture(this->index, &instruction);
        memory.lecture(this->index + 1, &arg);

        // Exécute chacune des instructions
        this->execute(instruction, arg, wheels, light, color);
    }
}

void Translator::execute(uint8_t instruction, uint8_t arg, WheelManager& wheels, LightManager& light, Color& color) {
    bool isActive = false;

    Mnemonic mnemonic = static_cast<Mnemonic>(instruction);

    if (isActive != true && mnemonic != Mnemonic::DBT) return;

    switch (mnemonic) {
        case Mnemonic::DBT: // Début
            isActive = true;
            break;

        case Mnemonic::ATT: // Attendre
            for(uint8_t i = 0; i < arg ;i++)
                _delay_ms(25);
            break;

        case Mnemonic::DAL: // Allumer la del
            switch (arg)
            {
                case 1:
                    color = Color::GREEN;
                    break;

                case 2:
                    color = Color::RED;
                    break;

                default:
                    break;

            }
            light.setLight(color);
            break;

        case Mnemonic::DET: // Éteindre la del
            light.setLight(Color::OFF);
            break;

        case Mnemonic::SGO: // Jouer une sonorité
            /* code */
            break;

        case Mnemonic::SAR: // Arrêter de jouer la sonorité
            /* code */
            break;

        case Mnemonic::MAR1: // Arrêter les moteurs 1
        case Mnemonic::MAR2: // Arrêter les moteurs 2
            wheels.setSpeed(0);
            break;

        case Mnemonic::MAV: // Avancer
            wheels.setDirection(Direction::FORWARD);
            wheels.setSpeed(arg*100/255);
            break;

        case Mnemonic::MRE: // Reculer
            wheels.setDirection(Direction::BACKWARD);
            wheels.setSpeed(arg*100/255);
            break;

        case Mnemonic::TRD: // Tourner à droite
            wheels.setDirection(Direction::RIGHT);
            wheels.setSpeed(arg*100/255);
            break;

        case Mnemonic::TRG: // Tourner à gauche
            wheels.setDirection(Direction::LEFT);
            wheels.setSpeed(arg*100/255);
            break;

        case Mnemonic::DBC: // Début de boucle
            this->loopIndex = this->index+4;
            this->loopCounter = arg;
            break;

        case Mnemonic::FBC: // Fin de la boucle
            if (this->loopCounter > 0){
                    this->loopCounter --;
                    this->index = this->loopIndex;
                }
            break;
            
        case Mnemonic::FIN: // Fin
            isActive = false;
            return;

        default:
            break;
    }
}
