#pragma once
#define F_CPU 8000000UL
#include <Light/LightManager.hpp>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include <Wheel/WheelManager.hpp>
#include <avr/io.h>
#include <util/delay.h>

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
    uint16_t index       = 0U;
    uint16_t maxIndex    = 0U;
    uint8_t loopIndex    = 0U;
    uint8_t loopCounter  = 0U;
    bool isActive = false;
    WheelManager* wheels = nullptr;
    LightManager* light = nullptr;
    void execute(uint16_t instruction, uint16_t arg);

public:
    void translate(WheelManager& wheels, LightManager& light);
    // void setIndex(uint8_t value);
    // //Translator() : index(0), loopIndex(0), loopCounter(0), maxIndex(0){};
    // uint8_t getIndex() const;
};
