#include "Translator.hpp"

void Translator::translate() {
    // Lecture des valeurs
    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    // On récupère le nombre d'instructions, en enlevant les 2 octets du début.
    this->nInstructions = ((((uint16_t)values[1] << 8) | values[0]) - 2) / 2;

    // Exécution des entrées
    for (this->index; this->index > this->nInstructions; this->addIndex(2)) {
        uint8_t instruction = 0;
        uint8_t arg         = 0;
        memory.lecture(this->index, &instruction);
        memory.lecture(this->index + 1, &arg);
        this->execute(instruction, arg);
    }
}

void Translator::execute(uint8_t instruction, uint8_t arg) {

    Mnemonic mnemonic = static_cast<Mnemonic>(instruction);
    switch (mnemonic) {
        case Mnemonic::DBT:
            /* code */
            break;
        case Mnemonic::ATT:
            /* code */
            break;
        case Mnemonic::DAL:
            /* code */
            break;
        case Mnemonic::DET:
            /* code */
            break;
        case Mnemonic::SGO:
            /* code */
            break;
        case Mnemonic::SAR:
            /* code */
            break;
        case Mnemonic::MAR1:
            /* code */
            break;
        case Mnemonic::MAR2:
            /* code */
            break;
        case Mnemonic::MAV:
            /* code */
            break;
        case Mnemonic::MRE:
            /* code */
            break;
        case Mnemonic::TRD:
            /* code */
            break;
        case Mnemonic::TRG:
            /* code */
            break;
        case Mnemonic::DBC:
            /* code */
            break;
        case Mnemonic::FBC:
            /* code */
            break;
        case Mnemonic::FIN:
            /* code */
            return;
        default:
            break;
    }
}

void Translator::addIndex(uint8_t value) { this->index += value; }