#include "Translator.hpp"

void Translator::translate() {
    // Lecture des valeurs
    Memoire24CXXX memory;
    uint8_t values[2];
    memory.lecture(0, &values[0]);
    memory.lecture(1, &values[1]);

    this->nInstructions = ((uint16_t)values[1] << 8) | values[0];
    this->instructions[this->nInstructions];
    memory.lecture(2, instructions, this->nInstructions);

    // Exécution des entrées
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