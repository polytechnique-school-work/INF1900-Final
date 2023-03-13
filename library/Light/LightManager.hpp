/*
 * Utilité : Ce module permet la gestion des lumières.
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés: Aucun port obligatoire
 *  Entrée:
 *  Sortie:
 * */
#pragma once
#include <avr/io.h> 

enum class Color {OFF, GREEN, RED, AMBER};

class LightManager {
private:
    static const uint8_t DelayGREEN = 15;
    static const uint8_t DelayRED = 5;
    volatile uint8_t* regis;
    uint8_t firstPin;
    uint8_t secondPin;
    volatile uint8_t* port;

public:
    LightManager(volatile uint8_t* registre, volatile uint8_t* port, uint8_t pinFirst, uint8_t pinSecond);
    void setLight(Color color);
};