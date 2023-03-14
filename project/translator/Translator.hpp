#pragma once
#include <Memory/memoire_24.h>
#include <avr/io.h>
enum class Mnemonic {
    DBT  = 0b00000001, // Début
    ATT  = 0b00000010, // Attendre
    DAL  = 0b01000100, // Allumer la del
    DET  = 0b01000101, // Éteindre la del
    SGO  = 0b01001000, // Jouer une sonorité
    SAR  = 0b00001001, // Arrêter de jouer la sonorité
    MAR1 = 0b01100000, // Arrêter les moteurs 1
    MAR2 = 0b01100001, // Arrêter les moteurs 2
    MAV  = 0b01100010, // Avancer
    MRE  = 0b01100011, // Reculer
    TRD  = 0b01100100, // Tourner à droite
    TRG  = 0b01100101, // Tourner à gauche
    DBC  = 0b11000000, // Début de boucle
    FBC  = 0b11000001, // Fin de la boucle
    FIN  = 0b11111111, // Fin
};

class Translator {
private:
    uint16_t nInstructions;
    uint8_t index = 0;
    void execute(uint8_t instruction, uint8_t arg);

public:
    void translate();
};
