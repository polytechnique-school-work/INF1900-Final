#include "Translator.hpp"

void Translator::translate() {
    // Lecture des valeurs
    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    // On récupère le nombre d'instructions, en enlevant les 2 octets du début.
    this->maxIndex = ((((uint16_t)values[1] << 8) | values[0]) - 2);

    // Exécution des entrées
    for (this->index; this->index > this->maxIndex; this->index += 2) {
        uint8_t instruction = 0;
        uint8_t arg         = 0;
        memory.lecture(this->index, &instruction);
        memory.lecture(this->index + 1, &arg);

        // Exécute chacune des instructions
        this->execute(instruction, arg);
    }
}

void Translator::execute(uint8_t instruction, uint8_t arg) {

    bool isActive = false;

    Mnemonic mnemonic = static_cast<Mnemonic>(instruction);

    if (isActive != true && mnemonic != Mnemonic::DBT) return;

    switch (mnemonic) {
        case Mnemonic::DBT: // Début
            isActive = true;
            break;
        case Mnemonic::ATT: // Attendre
            /* code */
            break;
        case Mnemonic::DAL: // Allumer la del
            /* code */
            break;
        case Mnemonic::DET: // Éteindre la del
            /* code */
            break;
        case Mnemonic::SGO: // Jouer une sonorité
            /* code */
            break;
        case Mnemonic::SAR: // Arrêter de jouer la sonorité
            /* code */
            break;
        case Mnemonic::MAR1: // Arrêter les moteurs 1
        case Mnemonic::MAR2: // Arrêter les moteurs 2
            /* code */
            break;
        case Mnemonic::MAV: // Avancer
            /* code */
            break;
        case Mnemonic::MRE: // Reculer
            /* code */
            break;
        case Mnemonic::TRD: // Tourner à droite
            /* code */
            break;
        case Mnemonic::TRG: // Tourner à gauche
            /* code */
            break;
        case Mnemonic::DBC: // Début de boucle
            /* code */
            break;
        case Mnemonic::FBC: // Fin de la boucle
            /* code */
            break;
        case Mnemonic::FIN: // Fin
            isActive = false;
            return;
        default:
            break;
    }
}
