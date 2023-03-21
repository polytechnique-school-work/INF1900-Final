#include "Translator/Translator.hpp"
#include "Utils.hpp"

static const uint16_t TURNING_TIME = 550;
static const uint16_t DELAY        = 500;

void Translator::translate(WheelManager& wheels, LightManager& light) {
    this->soundPlayer.init();

    this->wheels = &wheels;
    this->light  = &light;


    /*  Lecture en mémoire des données. On commence par lire les 2 octets
     *  pour nous permettre de connaître la taille totale des octets à être lu.
     * */
    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    this->maxIndex = (uint16_t(values[0]) << 8) | values[1];

    uint8_t instruction = 0;
    uint8_t arg         = 0;

    /*  Lecture de chacun des octets, en prenant le premier octet comme instruction
     *  et le deuxième comme argument. Ensuite, exécute l'instruction.
     * */
    for (this->index = 2; this->index < this->maxIndex; this->index += 2) {
        memory.lecture(this->index, &instruction);
        memory.lecture(this->index + 1, &arg);

        DEBUG_PRINT(("Instruction"));
        DEBUG_PRINT((instruction));
        this->execute(instruction, arg);
    }
}

void Translator::execute(uint16_t instruction, uint16_t arg) {

    /*  Transormation d'une instruction (uint16_t) en Mnemonic
     * */
    Mnemonic mnemonic = static_cast<Mnemonic>(instruction);

    /*  Si le robot n'est pas actif et que l'instruction n'est pas
     *  celle de début, l'instruction est ignorée.
     * */
    if (isActive != true && mnemonic != Mnemonic::DBT) return;

    /*  Initialisation de l'ensemble des valeurs, étrangement
     *  si cette étape n'est pas effectuée, certaines erreurs
     *  apparaissent.
     * */
    uint8_t speed;
    uint16_t pourcentagePWM;
    Direction direction;

    switch (mnemonic) {
        case Mnemonic::DBT: // Début
            DEBUG_PRINT(("Instruction: begin"));
            isActive = true;
            break;

        case Mnemonic::ATT: // Attendre
            DEBUG_PRINT(("Instruction: wait"));
            for (uint8_t i = 0; i < arg; i++)
                _delay_ms(25);
            break;

        case Mnemonic::DAL: // Allumer la del
            DEBUG_PRINT(("Instruction: light on"));
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
            DEBUG_PRINT(("Instruction: light off"));
            this->light->setLight(Color::OFF);
            break;

        case Mnemonic::SGO: // Jouer une sonorité
            DEBUG_PRINT(("Instruction: play sound"));
            this->soundPlayer.playSound(arg);
            break;

        case Mnemonic::SAR: // Arrêter de jouer la sonorité
            DEBUG_PRINT(("Instruction: stop sound"));
            this->soundPlayer.reset();
            break;

        case Mnemonic::MAR1: // Arrêter les moteurs 1
        case Mnemonic::MAR2: // Arrêter les moteurs 2
            DEBUG_PRINT(("Instruction: stop motors"));
            this->wheels->setSpeed(0);
            this->wheels->update();
            break;

        case Mnemonic::MAV: // Avancer
            DEBUG_PRINT(("Instruction: move forward"));
            this->wheels->setDirection(Direction::FORWARD);
            this->wheels->setSpeed(arg * 100 / 255);
            this->wheels->update();
            break;

        case Mnemonic::MRE: // Reculer
            DEBUG_PRINT(("Instruction: move backward"));
            this->wheels->setDirection(Direction::BACKWARD);
            this->wheels->setSpeed(arg * 100 / 255);
            this->wheels->update();
            break;

        case Mnemonic::TRD: // Tourner à droite
            DEBUG_PRINT(("Instruction: turn right"));

            speed          = OCR2A; // Sur 255
            pourcentagePWM = speed / 255 * 100;

            direction      = this->wheels->getDirection();

            // Changement de direction
            this->wheels->setDirection(Direction::RIGHT);
            this->wheels->setSpeed(speed * 100 / 255);
            this->wheels->update();

            // Attente pour permettre une rotation de 90 degrés
            Utils::wait(TURNING_TIME / pourcentagePWM / 100);

            // Garder la même trajectoire précédente
            this->wheels->setSpeed(speed * 100 / 255);
            this->wheels->setDirection(direction);
            this->wheels->update();
            break;
        case Mnemonic::TRG: // Tourner à gauche
            DEBUG_PRINT(("Instruction: turn left"));

            speed          = OCR2A; // Sur 255
            pourcentagePWM = speed / 255 * 100;

            direction = this->wheels->getDirection();

            // Changement de direction
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
            DEBUG_PRINT(("Instruction: start loop"));
            this->loopIndex   = index;
            this->loopCounter = arg;
            break;

        case Mnemonic::FBC: // Fin de la boucle
            DEBUG_PRINT(("Instruction: end loop"));
            if (this->loopCounter > 0) {
                this->loopCounter--;
                index = this->loopIndex;
            }
            break;

        case Mnemonic::FIN: // Fin
            DEBUG_PRINT(("Instruction: end"));
            wheels->setSpeed(0);
            wheels->update();
            light->setLight(Color::OFF);
            this->soundPlayer.reset();
            isActive = false;
            return;

        default:
            DEBUG_PRINT(("Instruction: default"));
            break;
    }
}